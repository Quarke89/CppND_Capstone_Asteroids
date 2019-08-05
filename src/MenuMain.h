#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CTexture.h"
#include <vector>

class MenuMain
{
    public:
        MenuMain();
        ~MenuMain();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        void run();        

    private:

        SDL_Renderer* _prenderer;
        CTexture _textTitle;
        CTexture _textPlay;
        CTexture _textQuit;

};

