#include "ExplosionObject.h"

std::vector<SDL_Rect> ExplosionObject::_spriteClips = std::vector<SDL_Rect>();

ExplosionObject::ExplosionObject(Point pos, CTexture* tex)
    : GameObject(pos, tex), _currentClip(0), _width(AsteroidConstants::EXPLOSION_SPRITE_WIDTH), _height(AsteroidConstants::EXPLOSION_SPRITE_HEIGHT)
{
    if(_spriteClips.size() == 0){

        for(int y = 0; y < _pTex->getHeight(); y += AsteroidConstants::EXPLOSION_SPRITE_HEIGHT){
            for(int x = 0; x < _pTex->getWidth(); x += AsteroidConstants::EXPLOSION_SPRITE_WIDTH){
                SDL_Rect rect{x, y, AsteroidConstants::EXPLOSION_SPRITE_WIDTH, AsteroidConstants::EXPLOSION_SPRITE_HEIGHT};
                _spriteClips.push_back(rect);
            }
        }
        
    }
}

void ExplosionObject::setSize(AsteroidSize size)
{
    switch(size)
    {
        case AsteroidSize::BIG:
            _width = 128;
            _height = 128;
            break;
        case AsteroidSize::MED:
            _width = 64;
            _height = 64;
            break;
        case AsteroidSize::SMALL:
            _width = 32;
            _height = 32;
            break;
    }
    
}

void ExplosionObject::update(Uint32 updateTime)
{

    if(_currentClip < AsteroidConstants::EXPLOSION_SPRITE_NUM){
        Uint32 timeDelta = updateTime - _lastUpdated;
        if(timeDelta > 50){
            _currentClip++;        
            _lastUpdated = updateTime;
        }            
    }
    
}

void ExplosionObject::render(SDL_Renderer* renderer)
{
    if(_currentClip < AsteroidConstants::EXPLOSION_SPRITE_NUM){
         
        int xPosCenter = std::round(_pos.x);
        int yPosCenter = std::round(_pos.y);

        int left = xPosCenter - _width/2;
        int top = yPosCenter - _height/2;

        SDL_Rect dstRect{left, top, _width, _height};

        SDL_RenderCopy( renderer, _pTex->getTexture(), &_spriteClips[_currentClip], &dstRect);
    }
}

bool ExplosionObject::isAnimationDone()
{
    return _currentClip >= AsteroidConstants::EXPLOSION_SPRITE_NUM;
}