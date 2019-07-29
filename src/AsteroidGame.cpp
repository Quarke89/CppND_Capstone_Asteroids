#include "AsteroidGame.h"

void AsteroidGame::run()
{
    bool quit = false;
    SDL_Event e;
    int frames = 0;
    while(!quit){

        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }

        std::cout << frames << "\n";

        
        //Clear screen
        SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( _renderer );

        //Render background texture to screen
        _texBackground.render( _renderer, 0, 0 );


        //Update screen
        SDL_RenderPresent( _renderer );

        ++frames;
    }

}

bool AsteroidGame::loadMedia()
{
    bool success = true;

    if(!_texBackground.loadFromFile(_renderer, "img/background.png")){
        std::cout << "Failed to load background.png!\n";
        success = false;
    }

    return success;
}

AsteroidGame::AsteroidGame()
{
    init();
    loadMedia();
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
    _window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH, _SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(_window == nullptr){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    // Create renderer for window
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(_renderer == nullptr){
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

    _texBackground.free();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = nullptr;
    _window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

