#include "AsteroidObject.h"
#include "constants.h"
#include <cmath>

AsteroidObject::AsteroidObject(Point pos, CTexture* tex, CVector velocity)
    : GameObject(pos, tex, velocity)
{
    _type = texture2asteroid(tex->getType());
    _texType = tex->getType();
}

AsteroidType AsteroidObject::getType()
{
    return _type;
}

TextureType AsteroidObject::getTexType()
{
    return _texType;
}

AsteroidType AsteroidObject::texture2asteroid(TextureType type)
{
    switch(type)
    {
        case TextureType::TEX_ASTEROID_BIG_1:
        case TextureType::TEX_ASTEROID_BIG_2:
        case TextureType::TEX_ASTEROID_BIG_3:
            return AsteroidType::BIG;
        case TextureType::TEX_ASTEROID_MED_1:
        case TextureType::TEX_ASTEROID_MED_2:
        case TextureType::TEX_ASTEROID_MED_3:
            return AsteroidType::MED;
        case TextureType::TEX_ASTEROID_SMALL_1:
        case TextureType::TEX_ASTEROID_SMALL_2:
        case TextureType::TEX_ASTEROID_SMALL_3:
            return AsteroidType::SMALL;
    }
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
        SDL_RenderCopy( renderer, _pTex->getTexture(), &srcRect[i], &dstRect[i]);
    }

    _boundingBoxes = std::move(dstRect);
    // renderBoxes(renderer);

}

void AsteroidObject::renderBoxes(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
    for(const SDL_Rect& box: _boundingBoxes){
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

    _lastUpdated = updateTime;

}

std::vector<SDL_Rect>& AsteroidObject::getBoundingBoxes()
{
    return _boundingBoxes;
}