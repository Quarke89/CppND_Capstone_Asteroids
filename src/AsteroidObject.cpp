#include "AsteroidObject.h"
#include "constants.h"

AsteroidObject::AsteroidObject(CTexture* tex)
{
    _pTex = tex;
    _pos.x = 200;
    _pos.y = 200;
}

void AsteroidObject::update(Uint32 updateTime)
{
    _pos.x++;
    _pos.y++;
    if(_pos.x > AsteroidConstants::SCREEN_WIDTH){
        _pos.x = 0;
    }
    if(_pos.y > AsteroidConstants::SCREEN_HEIGHT){
        _pos.y = 0;
    }
    _rotation++;

}