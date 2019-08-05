#include "CTexture.h"

CTexture::CTexture()
{}

CTexture::CTexture(TextureType type) :_type(type)
{}

CTexture::~CTexture()
{
    free();
}

TextureType CTexture::getType()
{
    return _type;
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

bool CTexture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(textSurface == nullptr){
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    _texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(_texture == nullptr){
        std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
        return false;
    }
    
    //get image dimensions
    _width = textSurface->w;
    _height = textSurface->h;       
    SDL_FreeSurface(textSurface);        
    
    return true;
}

CTexture::CTexture(CTexture&& o)
{
    _texture = o._texture;
    _width = o._width;
    _height = o._height;
    _type = o._type;

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