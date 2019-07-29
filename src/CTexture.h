#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class CTexture
{
    public:
        CTexture();
        ~CTexture();

        CTexture(const CTexture& a) = delete;
        CTexture& operator=(const CTexture& ) = delete;

        CTexture(CTexture&& o);

        bool loadFromFile(SDL_Renderer* renderer, std::string path);

        SDL_Texture* getTexture();
        void free();        

        int getWidth();
        int getHeight();        

    private:

        SDL_Texture* _texture{nullptr};

        int _width{0};
        int _height{0};

};