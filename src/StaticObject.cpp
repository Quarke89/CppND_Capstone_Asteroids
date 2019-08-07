#include "StaticObject.h"

StaticObject::StaticObject(Point pos, CTexture* tex)
    : GameObject(pos, tex)
{}

void StaticObject::render(SDL_Renderer* renderer, SDL_Rect* dest)
{
    if(dest == nullptr){
        SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _pTex->getWidth(), _pTex->getHeight()};
        SDL_RenderCopy( renderer, _pTex->getTexture(), nullptr, &renderQuad);    
    }
    else{
        SDL_RenderCopy( renderer, _pTex->getTexture(), nullptr, dest);    
    }
}