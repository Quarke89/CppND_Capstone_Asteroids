#include "AsteroidGame.hpp"
#include <iostream>


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

        SDL_FillRect(_screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0x00 ) );
        
        //Update the surface
        SDL_UpdateWindowSurface( _window );



        //SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        //SDL_RenderClear(_renderer);

        //SDL_RenderPresent(_renderer);
        //SDL_Delay(1);
        ++frames;
    }

}

AsteroidGame::AsteroidGame()
{
    init();
}

AsteroidGame::~AsteroidGame()
{
    cleanup();
}

bool AsteroidGame::init()
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }
    if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
		std::cout << "Warning: Linear texture filtering not enabled!\n";
	}

    _window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREEN_WIDTH, _SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(_window == nullptr){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(_renderer == nullptr){
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
        return false;
    }
    _screenSurface = SDL_GetWindowSurface(_window);

    return true;
}

void AsteroidGame::cleanup()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = nullptr;
    _window = nullptr;
    SDL_Quit();
}

