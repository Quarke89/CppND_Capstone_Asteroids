#include "StaticObject.h"

StaticObject::StaticObject(Point pos, CTexture* tex)
    : GameObject(pos, tex)
{}

void StaticObject::render(SDL_Renderer_unique_ptr &renderer)
{
    SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer.get(), _pTex->getTexture(), nullptr, &renderQuad);    
}

void StaticObject::render(SDL_Renderer_unique_ptr &renderer, SDL_Rect* dest)
{
    SDL_RenderCopy( renderer.get(), _pTex->getTexture(), nullptr, dest);    
}