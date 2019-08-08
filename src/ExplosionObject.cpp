/* File:            ExplosionObject.cpp
 * Author:          Vish Potnis
 * Description:     - Derived class for explosion objects 
 *                  - Render animation sprites over time
 */


#include "ExplosionObject.h"

std::vector<SDL_Rect> ExplosionObject::_spriteClips = std::vector<SDL_Rect>();

ExplosionObject::ExplosionObject(const Point &pos, const CTexture& tex)
    : GameObject(pos, tex), _width(AsteroidConstants::EXPLOSION_SPRITE_WIDTH), _height(AsteroidConstants::EXPLOSION_SPRITE_HEIGHT), _currentClip(0)
{
    if(_spriteClips.size() == 0){

        for(int y = 0; y < tex.getHeight(); y += AsteroidConstants::EXPLOSION_SPRITE_HEIGHT){
            for(int x = 0; x < tex.getWidth(); x += AsteroidConstants::EXPLOSION_SPRITE_WIDTH){
                SDL_Rect rect{x, y, AsteroidConstants::EXPLOSION_SPRITE_WIDTH, AsteroidConstants::EXPLOSION_SPRITE_HEIGHT};
                _spriteClips.push_back(rect);
            }
        }
        
    }
}

void ExplosionObject::render(SDL_Renderer& renderer)
{
    if(_currentClip < AsteroidConstants::EXPLOSION_SPRITE_NUM){
         
        int xPosCenter = std::round(_pos.x);
        int yPosCenter = std::round(_pos.y);

        int left = xPosCenter - _width/2;
        int top = yPosCenter - _height/2;

        SDL_Rect dstRect{left, top, _width, _height};

        SDL_RenderCopy( &renderer, &_tex.getTexture(), &_spriteClips[_currentClip], &dstRect);
    }
}

void ExplosionObject::update(const Uint32 updateTime)
{

    if(_currentClip < AsteroidConstants::EXPLOSION_SPRITE_NUM){
        Uint32 timeDelta = updateTime - _lastUpdated;
        if(timeDelta > 50){
            _currentClip++;        
            _lastUpdated = updateTime;
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

bool ExplosionObject::isAnimationDone() const
{
    return _currentClip >= AsteroidConstants::EXPLOSION_SPRITE_NUM;
}