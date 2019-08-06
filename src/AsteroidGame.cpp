#include "AsteroidGame.h"


void AsteroidGame::run()
{
    runMainMenu();
    
    while(_state == GameState::RUNNING){
        initLevel();        
        runLevel();
        if(_state == GameState::LEVEL_COMPLETE){
            runNextMenu();
        }
        if(_state == GameState::GAMEOVER){
            runGameOverMenu();
        }
    }

}

void AsteroidGame::runLevel()
{
    SDL_Event event;

    while(_state == GameState::RUNNING){

        handleInput(event);

        updateObjects();
        renderObjects();

        checkShipCollision();            
        checkAsteroidCollision();      

        checkLevelCompleted(); 

        //TODO: add frame rate limitation
    }
    cleanupLevel();
}

void AsteroidGame::checkLevelCompleted()
{
    if(_asteroidHash.size() == 0){
        _state = GameState::LEVEL_COMPLETE;
        _currentLevel++;
        _currentColor = AsteroidObject::getNextColor(_currentColor);
    }
}


void AsteroidGame::runMainMenu()
{
    MenuMain mainMenu;
    mainMenu.init(_prenderer, _mainFonts);
    _state = mainMenu.run();
}

void AsteroidGame::runGameOverMenu()
{
    MenuGameOver gameOverMenu;
    gameOverMenu.init(_prenderer, _mainFonts);    
    _state = gameOverMenu.run();
    if(_state == GameState::PLAY_AGAIN){
        _currentLevel = 1;
        _score = 0;
        _state = GameState::RUNNING;
    }
}

void AsteroidGame::runNextMenu()
{
    MenuNext nextMenu;
    nextMenu.init(_prenderer, _mainFonts);
    _state = nextMenu.run();
}
    

void AsteroidGame::runPauseMenu()
{
    MenuPause pauseMenu;
    pauseMenu.init(_prenderer, _mainFonts);
    _state = pauseMenu.run();
}

void AsteroidGame::updateScore(int scoreIncrease)
{
    _score += scoreIncrease;

    SDL_Color whiteTextColor{255,255,255};
    std::stringstream ss("");
    ss << "Score: " << std::setw(5) << _score;
    _fontTextureScore.loadFromRenderedText(_prenderer, _mainFonts[static_cast<int>(FontType::MENU)], ss.str(), whiteTextColor);
}

void AsteroidGame::handleInput(SDL_Event &event)
{

    while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_QUIT){
            _state = GameState::QUIT;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_a:
                    static_cast<ShipObject*>(_pShip)->setRotateLeft(true);
                    break;
                case SDLK_d:
                    static_cast<ShipObject*>(_pShip)->setRotateRight(true);
                    break;
                case SDLK_w:
                    static_cast<ShipObject*>(_pShip)->setMoveForward(true);
                    break;
                case SDLK_s:
                    static_cast<ShipObject*>(_pShip)->setMoveBackward(true);
                    break;
                default:
                    break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_a:
                    static_cast<ShipObject*>(_pShip)->setRotateLeft(false);
                    break;
                case SDLK_d:
                    static_cast<ShipObject*>(_pShip)->setRotateRight(false);
                    break;
                case SDLK_w:
                    static_cast<ShipObject*>(_pShip)->setMoveForward(false);
                    break;
                case SDLK_s:
                    static_cast<ShipObject*>(_pShip)->setMoveBackward(false);
                    break;
                case SDLK_SPACE:
                    shootLaser();
                    break;
                case SDLK_ESCAPE:
                    runPauseMenu();
                    break;
                default:
                    break;

            }
        }
    }
}

void AsteroidGame::checkShipCollision()
{
    const SDL_Rect &shipRect = static_cast<ShipObject*>(_pShip)->getBoundingBox();
    
    for(auto const &asteroid: _asteroidHash){
        const std::vector<SDL_Rect> &boxes = static_cast<AsteroidObject*>(asteroid.second)->getBoundingBoxes();
        for(const SDL_Rect &box: boxes){
            if(checkCollision(shipRect, box)){
                _state = GameState::GAMEOVER;
                return;
            }
                
        }
    }
}

void AsteroidGame::checkAsteroidCollision()
{
    std::vector<int> asteroidCollideIdx;
    std::vector<int> laserCollideIdx;

    for(const auto &laser: _laserHash){
        const SDL_Rect &laserRect = static_cast<LaserObject*>(laser.second)->getBoundingBox();
        bool collide = false;

        for(const auto &asteroid: _asteroidHash){
            const std::vector<SDL_Rect> &boxes = static_cast<AsteroidObject*>(asteroid.second)->getBoundingBoxes();
            for(const SDL_Rect &box: boxes){
                if(checkCollision(laserRect, box)){
                    asteroidCollideIdx.push_back(asteroid.first);
                    collide = true;
                    break;
                }                    
            }
            if(collide){
                laserCollideIdx.push_back(laser.first);
                break;
            }

        }
    }

    for(int idx: asteroidCollideIdx){
        splitAsteroid(static_cast<AsteroidObject*>(_asteroidHash[idx]));
        delete _asteroidHash[idx];
        _asteroidHash.erase(idx);
        updateScore(10);
    }
    for(int idx: laserCollideIdx){
        delete _laserHash[idx];
        _laserHash.erase(idx);
    }
   
}

void AsteroidGame::shootLaser()
{
    Point laserPos = _pShip->getPos();
    double velocityAngle = _pShip->getRotation() - 90;

    CVector velocity{AsteroidConstants::LASER_VELOCITY, velocityAngle, VectorType::POLAR};

    createLaser(laserPos, velocity);
}

void AsteroidGame::createLaser(Point pos, CVector velocity)
{

    CTexture *pTex = &_mainTextures[static_cast<int>(TextureType::TEX_LASER)];

    GameObject *pLaser = GameObject::Create(ObjectType::LASER, pos, pTex, velocity, velocity.getAngle() + 90);
    
    _laserHash.insert(std::make_pair(pLaser->getID(), pLaser));

}

void AsteroidGame::splitAsteroid(AsteroidObject* asteroid)
{
    AsteroidSize currentSize = asteroid->getSize();
    Point pos = asteroid->getPos();

    if(currentSize == AsteroidSize::SMALL){
        createExplosion(pos, currentSize);
        return;
    }
        

    AsteroidSize nextSize = asteroid->getNextSize();

    int nextTexIdx = static_cast<int>(AsteroidObject::getAsteroidTexture(nextSize, _currentColor));
    CTexture* pTex = &_mainTextures[nextTexIdx];
    
    CVector currentVelocity = asteroid->getVelocity();
    CVector velocity1(currentVelocity.getMag(), currentVelocity.getAngle() - 45, VectorType::POLAR);
    CVector velocity2(currentVelocity.getMag(), currentVelocity.getAngle() + 45, VectorType::POLAR);

    createExplosion(pos, currentSize);
    createAsteroid(pos, velocity1, pTex, nextSize, _currentColor);
    createAsteroid(pos, velocity2, pTex, nextSize, _currentColor);

}

void AsteroidGame::createExplosion(Point pos, AsteroidSize size)
{   
    CTexture *pTex = &_mainTextures[static_cast<int>(TextureType::TEX_EXPLOSION_SPRITE_SHEET)];
    GameObject *pExplosion = GameObject::Create(ObjectType::EXPLOSION, pos, pTex);
    static_cast<ExplosionObject*>(pExplosion)->setSize(size);

    _explosionHash.insert(std::make_pair(pExplosion->getID(), pExplosion));
}

void AsteroidGame::createAsteroid(Point pos, CVector velocity, CTexture* pTex, AsteroidSize size, AsteroidColor color)
{

    GameObject *pAsteroid = GameObject::Create(ObjectType::ASTEROID, pos, pTex, velocity);
    static_cast<AsteroidObject*>(pAsteroid)->setAsteroidAttr(size, color);
    
    _asteroidHash.insert(std::make_pair(pAsteroid->getID(), pAsteroid));
}


bool AsteroidGame::checkCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void AsteroidGame::initShip()
{
    Point pos{AsteroidConstants::SCREEN_WIDTH/2, AsteroidConstants::SCREEN_HEIGHT/2};
    CVector velocity{0,0,VectorType::POLAR};

    CTexture* pTex = &_mainTextures[static_cast<int>(TextureType::TEX_SHIP)];

    _pShip = GameObject::Create(ObjectType::SHIP, pos, pTex, velocity);

}

void AsteroidGame::initLevel()
{

    int numAsteroid = _currentLevel;
    double asteroidVelocity = AsteroidConstants::INIT_ASTEROID_VELOCITY * std::pow(AsteroidConstants::ASTEROID_VELOCITY_MULTIPLIER, _currentLevel-1);
    Point pos = getRandomCorner();

    AsteroidSize size = AsteroidSize::BIG;
    CTexture* pTex = &_mainTextures[static_cast<int>(AsteroidObject::getAsteroidTexture(size, _currentColor))];    

    std::random_device rd;
    std::uniform_int_distribution<> randomAngle(0, 360);                
    
    for(int i = 0; i < numAsteroid; i++){
        double angle = static_cast<double>(randomAngle(rd));
        CVector velocity{asteroidVelocity, angle, VectorType::POLAR};

        createAsteroid(pos, velocity, pTex, size, _currentColor);
    }
    initShip();

    SDL_Color whiteTextColor{255,255,255};

    std::stringstream ss("");
    ss << "Level: " << _currentLevel;
    _fontTextureLevel.loadFromRenderedText(_prenderer, _mainFonts[static_cast<int>(FontType::MENU)], ss.str(), whiteTextColor);

    Point levelPos{AsteroidConstants::FONT_LEVEL_POS_X, AsteroidConstants::FONT_LEVEL_POS_Y};
    _fontObjectLevel = GameObject::Create(ObjectType::STATIC, levelPos, &_fontTextureLevel); 

    ss.str("");
    ss << "Score: " << std::setw(5) << _score;
    _fontTextureScore.loadFromRenderedText(_prenderer, _mainFonts[static_cast<int>(FontType::MENU)], ss.str(), whiteTextColor);

    Point scorePos{AsteroidConstants::FONT_SCORE_POS_X, AsteroidConstants::FONT_SCORE_POS_Y};
    _fontObjectScore = GameObject::Create(ObjectType::STATIC, scorePos, &_fontTextureScore); 

}

Point AsteroidGame::getRandomCorner()
{
    std::random_device rd;
    std::uniform_int_distribution<> rdCorner(0, 3);

    int corner = rdCorner(rd);

    switch(corner){
        case 0:     return Point{0, 0};
        case 1:     return Point{0, AsteroidConstants::SCREEN_HEIGHT};
        case 2:     return Point{AsteroidConstants::SCREEN_WIDTH, 0};
        case 3:     return Point{AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT};
        default:    return Point{0, 0};
    }
}

void AsteroidGame::updateObjects()
{
    Uint32 time = SDL_GetTicks();
    for(auto& asteroid: _asteroidHash){
        asteroid.second->update(time);
    }
    for(auto& laser: _laserHash){
        laser.second->update(time);
    }
    for(auto& laser: _laserHash){
        if(static_cast<LaserObject*>(laser.second)->checkOffscreen()){
            delete laser.second;
            _laserHash.erase(laser.first);
        }
    }
    for(auto& explosion: _explosionHash){
        explosion.second->update(time);
    }
    _pShip->update(time);

}

void AsteroidGame::renderObjects()
{
    //Clear screen
    SDL_SetRenderDrawColor( _prenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear( _prenderer );

    for(auto& explosion: _explosionHash){
        explosion.second->render(_prenderer);
        if(static_cast<ExplosionObject*>(explosion.second)->isAnimationDone()){
            delete explosion.second;
            _explosionHash.erase(explosion.first);
        }
    }
    for(auto const& asteroid: _asteroidHash){
        asteroid.second->render(_prenderer);
    }
    for(auto const& laser: _laserHash){
        laser.second->render(_prenderer);
    }    
    _pShip->render(_prenderer);

    _fontObjectLevel->render(_prenderer);
    _fontObjectScore->render(_prenderer);

    //Update screen
    SDL_RenderPresent( _prenderer );

}

bool AsteroidGame::loadTextures()
{
    bool success = true;

    for(int i = 0; i < static_cast<unsigned int>(TextureType::TEX_TOTAL); i++){
        CTexture tmp;
        success &= tmp.loadFromFile(_prenderer, getTexturePath(static_cast<TextureType>(i)));
        _mainTextures.push_back(std::move(tmp));
    }
    return success;
}

bool AsteroidGame::loadFonts()
{
    bool success = true;

    for(int i = 0; i < static_cast<unsigned int>(FontType::FONT_TOTAL); i++){
        TTF_Font *pFont;
        switch(static_cast<FontType>(i)){
            case FontType::TITLE1:
                pFont = TTF_OpenFont( "fonts/Alexis Laser Italic.ttf", AsteroidConstants::FONTSIZE_TITLE1);
                break;
            case FontType::TITLE2:
                pFont = TTF_OpenFont( "fonts/Alexis Italic.ttf", AsteroidConstants::FONTSIZE_TITLE2);
                break;
            case FontType::MENU:
                pFont = TTF_OpenFont( "fonts/Alexis.ttf", AsteroidConstants::FONTSIZE_MENU);
                break;
            case FontType::TEXT:
                pFont = TTF_OpenFont( "fonts/Alexis.ttf", AsteroidConstants::FONTSIZE_TEXT);
                break;
            default: break;
        }
        if(pFont == nullptr){
            std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << "\n";		
		    success &= false;
	    }
        else{
            _mainFonts.push_back(pFont);
        }        
    }

    return success;
}

std::string AsteroidGame::getTexturePath(TextureType type)
{
    switch(type){
        case TextureType::TEX_BACKGROUND: return "img/background.png";
        case TextureType::TEX_ASTEROID_BIG_1: return "img/asteroid_big1.png";
        case TextureType::TEX_ASTEROID_BIG_2: return "img/asteroid_big2.png";
        case TextureType::TEX_ASTEROID_BIG_3: return "img/asteroid_big3.png";
        case TextureType::TEX_ASTEROID_MED_1: return "img/asteroid_med1.png";
        case TextureType::TEX_ASTEROID_MED_2: return "img/asteroid_med2.png";
        case TextureType::TEX_ASTEROID_MED_3: return "img/asteroid_med3.png";
        case TextureType::TEX_ASTEROID_SMALL_1: return "img/asteroid_small1.png";
        case TextureType::TEX_ASTEROID_SMALL_2: return "img/asteroid_small2.png";
        case TextureType::TEX_ASTEROID_SMALL_3: return "img/asteroid_small3.png";
        case TextureType::TEX_LASER: return "img/laser.png";
        case TextureType::TEX_SHIP: return "img/ship.png";
        case TextureType::TEX_EXPLOSION_SPRITE_SHEET: return "img/explosion_sheet.png";
        default: return "";
    }
}

AsteroidGame::AsteroidGame()
    :_currentColor(AsteroidColor::GREY), _state(GameState::RUNNING), _currentLevel(1), _score(0)
{
    if(!init())
        exit(0);
    if(!loadTextures())
        exit(0);
    if(!loadFonts())
        exit(0);

    Point backgroundPos{0,0};
    _backgroundObject = GameObject::Create(ObjectType::STATIC, backgroundPos, &_mainTextures[static_cast<int>(TextureType::TEX_BACKGROUND)]);

}

AsteroidGame::~AsteroidGame()
{
    cleanup();
}

bool AsteroidGame::init()
{

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }
    // Set texture filtering ot linear
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
		std::cout << "Warning: Linear texture filtering not enabled!\n";
	}

    // Create window
    _pwindow = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(_pwindow == nullptr){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create renderer for window
    _prenderer = SDL_CreateRenderer(_pwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(_prenderer == nullptr){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
        return false;
    }
    
    // initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imgFlags) & imgFlags) ){
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " <<  TTF_GetError() << "\n";
        return false;
    }

    return true;
}

void AsteroidGame::cleanupLevel()
{
    if(_pShip)
        delete _pShip;
    _pShip = nullptr; 

    for(auto& explosion: _explosionHash){
        delete explosion.second;
    }
    _explosionHash.clear();

    for(auto& laser: _laserHash){
        delete laser.second;
    }
    _laserHash.clear();

    for(auto& asteroid: _asteroidHash){
        delete asteroid.second;
    }
    _asteroidHash.clear();
}

void AsteroidGame::cleanup()
{
    cleanupLevel();

    for(auto& tex: _mainTextures){
        tex.free();
    }

    for(auto& font: _mainFonts){
        TTF_CloseFont(font);
    }

    SDL_DestroyRenderer(_prenderer);
    SDL_DestroyWindow(_pwindow);
    _prenderer = nullptr;
    _pwindow = nullptr;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

