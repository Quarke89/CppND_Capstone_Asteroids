#include "ShipObject.h"
#include "constants.h"

ShipObject::ShipObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime)
    : GameObject(pos, tex, velocity, acceleration, updateTime), _rotateLeft(false), _rotateRight(false), _directionAngle(-90)
{
    _width = _pTex->getWidth()/1.5;
    _height = _pTex->getHeight()/1.5;
}

void ShipObject::update(Uint32 updateTime)
{

    if(_moveForward || _moveBackward){
        if(_moveForward){
            _velocity = CVector(150, _directionAngle, VectorType::POLAR);
        }
        else{
            _velocity = CVector(-150, _directionAngle, VectorType::POLAR);
        }
    }
    else{
        _velocity = CVector(0, 0, VectorType::POLAR);
    }

    if(_rotateLeft ^ _rotateRight){
        if(_rotateLeft){
            _rotation -= 5;
            _directionAngle -= 5;
        }
        else{
            _rotation += 5;
            _directionAngle += 5;
        }

    }

    double timeDelta = static_cast<double>(updateTime - _lastUpdated)/1000;

    _pos.x += _velocity.getXProjection() * timeDelta;
    _pos.y += _velocity.getYProjection() * timeDelta;

    _lastUpdated = updateTime;
}

void ShipObject::render(SDL_Renderer* renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int left = xPosCenter - _width/2;
    int top = yPosCenter - _height/2;


    SDL_Rect dstRect{left, top, _width, _height};

    SDL_RenderCopyEx( renderer, _pTex->getTexture(), nullptr, &dstRect, _rotation, nullptr, SDL_FLIP_NONE);

    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
    // SDL_RenderDrawRect(renderer, &dstRect);

    _boundingBox = std::move(dstRect);

}

void ShipObject::setRotateLeft(bool val)
{
    _rotateLeft = val;
}

void ShipObject::setRotateRight(bool val)
{
    _rotateRight = val;
}

void ShipObject::setMoveForward(bool val)
{
    _moveForward = val;
}

void ShipObject::setMoveBackward(bool val)
{
    _moveBackward = val;
}

SDL_Rect& ShipObject::getBoundingBox() 
{
    return _boundingBox;
}

Point ShipObject::getTipPos()
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int top = yPosCenter - _height/2;

    Point tip{static_cast<double>(xPosCenter), static_cast<double>(top)};

    return tip;
}
