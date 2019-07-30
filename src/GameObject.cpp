#include "GameObject.h"
#include "AsteroidObject.h"

GameObject::GameObject()
{}

GameObject* GameObject::Create(ObjectType type, CTexture* tex)
{
    switch(type){
        case ObjectType::ASTEROID: return new AsteroidObject(tex);
        default: return nullptr;

    }
}

void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{_pos.x, _pos.y, _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer, _pTex->getTexture(), NULL, &renderQuad );

}