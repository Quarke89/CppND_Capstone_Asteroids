#include "GameObject.h"
#include "AsteroidObject.h"


GameObject::GameObject(Point pos, CTexture* pTex, CVector velocity, CVector acceleration)
    :_pos(pos), _pTex(pTex), _velocity(velocity), _acceleration(acceleration)
{}

GameObject* GameObject::Create(Point pos, ObjectType type, CTexture* tex, CVector velocity, CVector acceleration)
{
    switch(type){
        case ObjectType::ASTEROID: return new AsteroidObject(pos, tex, velocity, acceleration);
        default: 
            return nullptr;

    }
}

void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer, _pTex->getTexture(), NULL, &renderQuad );    

}