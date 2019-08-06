#include "AsteroidGame.h"
#include "constants.h"
#include "AsteroidObject.h"
#include "ShipObject.h"
#include "LaserObject.h"
#include <random>

void AsteroidGame::run()
{
    _mainmenu.run();
    // SDL_Event e;
    // int frames = 0;
    // double fps;
    // while(_running){

    //     handleInput(e);

    //     //Clear screen
    //     SDL_SetRenderDrawColor( _prenderer, 0x00, 0x00, 0x00, 0xFF );
    //     SDL_RenderClear( _prenderer );

    //     updateObjects();
    //     renderObjects();


    //     //Update screen
    //     SDL_RenderPresent( _prenderer );

    //     if(checkShipCollision())
    //         _running = false;

    //     checkAsteroidCollision();
        

    //     // Uint32 ticks = SDL_GetTicks();
    //     // fps = static_cast<double>(frames)/ticks * 1000;

    //     // std::cout << fps << std::endl;

    //     ++frames;
    // }

}



void AsteroidGame::handleInput(SDL_Event &e)
{

    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            _running = false;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
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
        else if(e.type == SDL_KEYUP)
        {
            switch(e.key.keysym.sym)
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
                default:
                    break;

            }
        }
    }
}

bool AsteroidGame::checkShipCollision()
{
    const SDL_Rect &shipRect = static_cast<ShipObject*>(_pShip)->getBoundingBox();
    
    for(auto const &asteroid: _asteroidHash){
        const std::vector<SDL_Rect> &boxes = static_cast<AsteroidObject*>(asteroid.second)->getBoundingBoxes();
        for(const SDL_Rect &box: boxes){
            if(checkCollision(shipRect, box))
                return true;
        }
    }
    return false;
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
    if(asteroid->getSize() == AsteroidSize::SMALL)
        return;

    AsteroidSize nextSize = asteroid->getNextSize();
    int nextTexIdx = static_cast<int>(AsteroidObject::getAsteroidTexture(nextSize, _currentColor));
    CTexture* pTex = &_mainTextures[nextTexIdx];

    Point pos = asteroid->getPos();

    CVector currentVelocity = asteroid->getVelocity();
    CVector velocity1(currentVelocity.getMag(), currentVelocity.getAngle() - 45, VectorType::POLAR);
    CVector velocity2(currentVelocity.getMag(), currentVelocity.getAngle() + 45, VectorType::POLAR);

    createAsteroid(pos, velocity1, pTex, nextSize, _currentColor);
    createAsteroid(pos, velocity2, pTex, nextSize, _currentColor);

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

    int numAsteroid = 2;
    std::random_device rd;
    std::uniform_int_distribution<> distx(0, AsteroidConstants::SCREEN_WIDTH);
    std::uniform_int_distribution<> disty(0, AsteroidConstants::SCREEN_HEIGHT);
    std::uniform_int_distribution<> distAngle(0, 360);
    std::uniform_int_distribution<> distVelocity(100, 200);

    Point pos{0, 0};

    AsteroidSize size = AsteroidSize::BIG;

    CTexture* pTex = &_mainTextures[static_cast<int>(AsteroidObject::getAsteroidTexture(size, _currentColor))];

    for(int i = 0; i < numAsteroid; i++){
        double angle = static_cast<double>(distAngle(rd));
        CVector velocity{static_cast<double>(distVelocity(rd)), angle, VectorType::POLAR};

        createAsteroid(pos, velocity, pTex, size, _currentColor);

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
    _pShip->update(time);

}

void AsteroidGame::renderObjects()
{
    for(auto const& asteroid: _asteroidHash){
        asteroid.second->render(_prenderer);
    }
    for(auto const& laser: _laserHash){
        laser.second->render(_prenderer);
    }
    _pShip->render(_prenderer);

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
        default: return "";
    }
}

AsteroidGame::AsteroidGame()
    :_running(true), _currentColor(AsteroidColor::GREY)
{
    if(!init())
        exit(0);
    if(!loadTextures())
        exit(0);
    if(!loadFonts())
        exit(0);

    _mainmenu.init(_prenderer, _mainFonts);

    initLevel();
    initShip();
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

void AsteroidGame::cleanup()
{
    if(_pShip)
        delete _pShip;
    _pShip = nullptr; 

    for(auto& laser: _laserHash){
        delete laser.second;
    }

    for(auto& asteroid: _asteroidHash){
        delete asteroid.second;
    }

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

