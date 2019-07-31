#include "GameObject.h"
#include "AsteroidObject.h"


GameObject::GameObject(Point pos, CTexture* pTex)
    :_pos(pos), _pTex(pTex)
{}

GameObject* GameObject::Create(Point pos, ObjectType type, CTexture* tex)
{
    switch(type){
        case ObjectType::ASTEROID: return new AsteroidObject(pos, tex);
        default: 
            return nullptr;

    }
}

void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{_pos.x, _pos.y, _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer, _pTex->getTexture(), NULL, &renderQuad );    

}