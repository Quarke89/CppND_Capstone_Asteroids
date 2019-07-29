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

        bool loadFromFile(SDL_Renderer* renderer, std::string path);

        void free();
        void render(SDL_Renderer* renderer, int x, int y);

        int getWidth();
        int getHeight();        

    private:

        SDL_Texture* _texture{nullptr};

        int _width{0};
        int _height{0};

};