#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "CTexture.h"

class AsteroidGame{

    public:
        AsteroidGame();
        ~AsteroidGame();

        bool init();
        void run();
        void cleanup();

        bool loadMedia();
        
        void renderBackgrond();
        

    private:

        static constexpr int _SCREEN_WIDTH{800};
        static constexpr int _SCREEN_HEIGHT{600};
        
        SDL_Window* _window{nullptr};
        SDL_Renderer* _renderer{nullptr};

        CTexture _texBackground;

};