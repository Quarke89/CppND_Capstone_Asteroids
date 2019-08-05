#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CTexture.h"
#include <vector>

class MenuMain
{
    public:
        MenuMain(std::vector<TTF_Font*> &mainFonts);
        ~MenuMain();

        void free();

    private:

        CTexture _textTitle;
        CTexture _textPlay;
        CTexture _textQuit;

};

MenuMain::MenuMain(std::vector<TTF_Font*> &mainFonts)
{

}

MenuMain::~MenuMain()
{
    free();
}