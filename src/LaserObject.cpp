#include "LaserObject.h"
#include "constants.h"

LaserObject::LaserObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, double rotation)
    : GameObject(pos, tex, velocity, acceleration)
{
    _rotation = rotation;
    _width = _pTex->getWidth()/20;
    _height = _pTex->getHeight()/24;
}

void LaserObject::update(Uint32 updateTime)
{

    double timeDelta = static_cast<double>(updateTime - _lastUpdated)/1000;

    _pos.x += _velocity.getXProjection() * timeDelta;
    _pos.y += _velocity.getYProjection() * timeDelta;

    _lastUpdated = updateTime;
}

void LaserObject::render(SDL_Renderer* renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int left = xPosCenter - _width/2;
    int top = yPosCenter - _height/2;

    SDL_Rect dstRect{left, top, _width, _height};

    SDL_RenderCopyEx( renderer, _pTex->getTexture(), nullptr, &dstRect, _rotation, nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
    SDL_RenderDrawRect(renderer, &dstRect);

    _boundingBox = std::move(dstRect);

}
