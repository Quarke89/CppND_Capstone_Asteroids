#include "CTexture.h"

CTexture::CTexture(){}

CTexture::~CTexture()
{
    free();
}

bool CTexture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
    free();

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }
    
    _texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(_texture == nullptr){
        std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << "\n";
        return false;
    }
    
    //get image dimensions
    _width = loadedSurface->w;
    _height = loadedSurface->h;       
    SDL_FreeSurface(loadedSurface);        
    
    return true;

}

CTexture::CTexture(CTexture&& o)
{
    _texture = o._texture;
    _width = o._width;
    _height = o._height;

    o._texture = nullptr;
    o._width = 0;
    o._height = 0;
}

SDL_Texture* CTexture::getTexture()
{
    return _texture;
}

void CTexture::free()
{
    if(_texture != nullptr){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
        _width = 0;
        _height = 0;
    }
}

int CTexture::getWidth()
{
    return _width;
}

int CTexture::getHeight()
{
    return _height;
}