#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "constants.h"


class CTexture
{
    public:
        CTexture(TextureType type);
        CTexture();
        ~CTexture();

        CTexture(const CTexture& a) = delete;
        CTexture& operator=(const CTexture& ) = delete;

        CTexture(CTexture&& o);

        bool loadFromFile(SDL_Renderer* renderer, std::string path);
        bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor);

        SDL_Texture* getTexture();
        void free();        

        int getWidth();
        int getHeight();

        TextureType getType();        

    private:

        TextureType _type;
        SDL_Texture* _texture{nullptr};

        int _width{0};
        int _height{0};

};