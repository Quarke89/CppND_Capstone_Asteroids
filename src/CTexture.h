#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

enum class TextureType
{    
    TEX_ASTEROID_BIG_1,
    TEX_ASTEROID_MED_1,
    TEX_ASTEROID_SMALL_1,
    TEX_ASTEROID_BIG_2,
    TEX_ASTEROID_MED_2,
    TEX_ASTEROID_SMALL_2,
    TEX_ASTEROID_BIG_3,
    TEX_ASTEROID_MED_3,
    TEX_ASTEROID_SMALL_3,
    TEX_SHIP,
    TEX_LASER,
    TEX_BACKGROUND,
    TEX_TOTAL
};

class CTexture
{
    public:
        CTexture(TextureType type);
        ~CTexture();

        CTexture(const CTexture& a) = delete;
        CTexture& operator=(const CTexture& ) = delete;

        CTexture(CTexture&& o);

        bool loadFromFile(SDL_Renderer* renderer, std::string path);

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