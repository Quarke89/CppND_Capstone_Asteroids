#include "AsteroidGame.h"
#include "constants.h"
#include <random>

void AsteroidGame::run()
{
    bool quit = false;
    SDL_Event e;
    int frames = 0;
    double fps;
    while(!quit){

        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        // Uint32 ticks = SDL_GetTicks();
        // fps = static_cast<double>(frames)/ticks * 1000;

        // std::cout << fps << std::endl;

        //Clear screen
        SDL_SetRenderDrawColor( _prenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( _prenderer );

        updateObjects();
        renderObjects();


        //Update screen
        SDL_RenderPresent( _prenderer );
        ++frames;
    }

}

void AsteroidGame::initLevel()
{
    std::random_device rd;
    std::uniform_int_distribution<> distx(0, AsteroidConstants::SCREEN_WIDTH);
    std::uniform_int_distribution<> disty(0, AsteroidConstants::SCREEN_HEIGHT);
    std::uniform_int_distribution<> distAngle(0, 360);
    std::uniform_int_distribution<> distVelocity(100, 200);

    Point pos{AsteroidConstants::SCREEN_WIDTH/2, AsteroidConstants::SCREEN_HEIGHT/2};
    CVector acceleration{0,0};

    for(int i = 0; i < 10; i++){
        CVector velocity{static_cast<double>(distVelocity(rd)), static_cast<double>(distAngle(rd))};

        _gameObjects.push_back(GameObject::Create(pos, ObjectType::ASTEROID, &_mainTextures[static_cast<int>(TextureType::TEX_ASTEROID_SMALL_1)], velocity, acceleration) );
    }

}

void AsteroidGame::updateObjects()
{
    Uint32 time = SDL_GetTicks();
    for(auto& obj: _gameObjects){
        obj->update(time);
    }
}

void AsteroidGame::renderObjects()
{
    for(auto const& obj: _gameObjects){
        obj->render(_prenderer);
    }
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
        default: return "";
    }
}

AsteroidGame::AsteroidGame()
{
    if(!init())
        exit(0);
    if(!loadTextures())
        exit(0);

    initLevel();
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
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() <<"\n";
        return false;
    }

    return true;
}

void AsteroidGame::cleanup()
{
    for(auto& obj: _gameObjects){
        delete obj;
    }

    for(auto& tex: _mainTextures){
        tex.free();
    }

    SDL_DestroyRenderer(_prenderer);
    SDL_DestroyWindow(_pwindow);
    _prenderer = nullptr;
    _pwindow = nullptr;

    IMG_Quit();
    SDL_Quit();
}

