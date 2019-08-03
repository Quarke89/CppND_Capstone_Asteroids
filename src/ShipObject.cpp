#include "ShipObject.h"
#include "constants.h"

ShipObject::ShipObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration)
    : GameObject(pos, tex, velocity, acceleration)
{
}

void ShipObject::update(Uint32 updateTime)
{

}

void ShipObject::render(SDL_Renderer* renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int width = _pTex->getWidth();
    int height = _pTex->getHeight();


    SDL_Rect dstRect{xPosCenter, yPosCenter, width, height};

    SDL_RenderCopyEx( renderer, _pTex->getTexture(), nullptr, &dstRect, _rotation, nullptr, SDL_FLIP_NONE);

}
