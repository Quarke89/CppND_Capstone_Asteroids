#include "AsteroidObject.h"
#include "constants.h"
#include <cmath>

AsteroidObject::AsteroidObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration)
    : GameObject(pos, tex, velocity, acceleration)
{
}

void AsteroidObject::render(SDL_Renderer* renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    std::vector<SDL_Rect> srcRect;
    std::vector<SDL_Rect> dstRect;

    int width = _pTex->getWidth();
    int height = _pTex->getHeight();

    calculateRenderRectangles(xPosCenter, yPosCenter, width, height, AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT, srcRect, dstRect);    

    for(int i = 0; i < srcRect.size(); i++){
        SDL_RenderCopyEx( renderer, _pTex->getTexture(), &srcRect[i], &dstRect[i], _rotation, nullptr, SDL_FLIP_NONE);
    }

    _boundingBoxs = std::move(dstRect);
    //renderBoxes(renderer);

}

void AsteroidObject::renderBoxes(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
    for(const SDL_Rect& box: _boundingBoxs){
        SDL_RenderDrawRect(renderer, &box);
    }
}


void AsteroidObject::update(Uint32 updateTime)
{

    double timeDelta = static_cast<double>(updateTime - _lastUpdated)/1000;

    _pos.x += _velocity.getXProjection() * timeDelta;
    _pos.y += _velocity.getYProjection() * timeDelta;

    if(_pos.x >= AsteroidConstants::SCREEN_WIDTH){
        _pos.x = 0;
    }
    if(_pos.x < 0){
        _pos.x = AsteroidConstants::SCREEN_WIDTH;
    }

    if(_pos.y >= AsteroidConstants::SCREEN_HEIGHT){
        _pos.y = 0;
    }
    if(_pos.y < 0){
        _pos.y = AsteroidConstants::SCREEN_HEIGHT;
    }
    //_rotation++;

    _lastUpdated = updateTime;

}