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
    
        bool loadFromFile(SDL_Renderer& renderer, std::string path);
        bool loadFromRenderedText(SDL_Renderer& renderer, TTF_Font* font, std::string text, SDL_Color textColor);

        SDL_Texture& getTexture() const;
        void free();        

        int getWidth() const;
        int getHeight() const;

    private:

        SDL_Texture* _ptexture{nullptr};
        SDL_Texture_unique_ptr _texture;

        int _width{0};
        int _height{0};

};