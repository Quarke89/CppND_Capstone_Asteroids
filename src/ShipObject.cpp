#include "ShipObject.h"
#include "constants.h"

ShipObject::ShipObject(const Point& pos, const CTexture& tex, CVector velocity)
    : GameObject(pos, tex, velocity), _rotateLeft(false), _rotateRight(false), _moveForward(false), _moveBackward(false)
{
    _width = _tex.getWidth()/AsteroidConstants::SCALE_SHIP_W;
    _height = _tex.getHeight()/AsteroidConstants::SCALE_SHIP_H;
}

void ShipObject::update(Uint32 updateTime)
{

    if(_moveForward || _moveBackward){
        if(_moveForward){
            _velocity = CVector(150, _rotation-90, VectorType::POLAR);
        }
        else{
            _velocity = CVector(-150, _rotation-90, VectorType::POLAR);
        }
    }
    else{
        _velocity = CVector(0, 0, VectorType::POLAR);
    }

    if(_rotateLeft ^ _rotateRight){
        if(_rotateLeft){
            _rotation -= 5;
        }
        else{
            _rotation += 5;
        }
        if(_rotation < 0) _rotation += 360;
        if(_rotation >= 360) _rotation -= 360;
    }

    double timeDelta = static_cast<double>(updateTime - _lastUpdated)/1000;

    _pos.x += _velocity.getXProjection() * timeDelta;
    _pos.y += _velocity.getYProjection() * timeDelta;

    _lastUpdated = updateTime;
}

void ShipObject::render(SDL_Renderer& renderer)
{
    int xPosCenter = std::round(_pos.x);
    int yPosCenter = std::round(_pos.y);

    int left = xPosCenter - _width/2;
    int top = yPosCenter - _height/2;


    SDL_Rect dstRect{left, top, _width, _height};

    SDL_RenderCopyEx( &renderer, &_tex.getTexture(), nullptr, &dstRect, _rotation, nullptr, SDL_FLIP_NONE);

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
