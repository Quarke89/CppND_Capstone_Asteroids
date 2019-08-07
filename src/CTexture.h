#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <memory>
#include "constants.h"
#include "utility.h"


class CTexture
{
    public:
        CTexture();
        ~CTexture();

        CTexture(const CTexture& a) = delete;
        CTexture& operator=(const CTexture& ) = delete;

        CTexture(CTexture&& o);
    
        bool loadFromFile(SDL_Renderer_unique_ptr &renderer, std::string path);
        bool loadFromRenderedText(SDL_Renderer_unique_ptr &renderer, TTF_Font* font, std::string text, SDL_Color textColor);

        SDL_Texture* getTexture();
        void free();        

        int getWidth();
        int getHeight();

    private:

        SDL_Texture* _texture{nullptr};

        int _width{0};
        int _height{0};

};