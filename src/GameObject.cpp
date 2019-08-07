#include "GameObject.h"
#include "AsteroidObject.h"
#include "ShipObject.h"
#include "LaserObject.h"
#include "StaticObject.h"
#include "ExplosionObject.h"

int GameObject::_count = 0;

GameObject::GameObject(Point pos, CTexture* pTex)
    : GameObject(pos, pTex, CVector()){}


GameObject::GameObject(Point pos, CTexture* pTex, CVector velocity)
    : GameObject(pos, pTex, velocity, 0){}

GameObject::GameObject(Point pos, CTexture* pTex, CVector velocity, double rotation)
    : _pos(pos), _pTex(pTex), _velocity(velocity), _rotation(rotation), _lastUpdated(SDL_GetTicks()), _id(++_count){}


void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer, _pTex->getTexture(), NULL, &renderQuad );    

}

void GameObject::update(Uint32 updateTime)
{
    _lastUpdated = updateTime;
}

std::unique_ptr<GameObject> GameObject::Create(ObjectType type, Point pos, CTexture* tex, CVector velocity, double rotation)
{
    switch(type){
        case ObjectType::STATIC:    return std::unique_ptr<GameObject>(new StaticObject(pos, tex));
        case ObjectType::ASTEROID:  return std::unique_ptr<GameObject>(new AsteroidObject(pos, tex, velocity));
        case ObjectType::SHIP:      return std::unique_ptr<GameObject>(new ShipObject(pos, tex, velocity));
        case ObjectType::LASER:     return std::unique_ptr<GameObject>(new LaserObject(pos, tex, velocity, rotation));
        case ObjectType::EXPLOSION: return std::unique_ptr<GameObject>(new ExplosionObject(pos, tex));
        default: 
            return nullptr;
    }
}

CVector GameObject::getVelocity() const { return _velocity;}
int GameObject::getID() const { return _id;}
Point GameObject::getPos() const { return _pos;}
double GameObject::getRotation() const { return _rotation;}



void GameObject::calculateRenderRectangles(int objPosX, int objPosY, int objWidth, int objHeight, int screenWidth, int screenHeight, 
                                        std::vector<SDL_Rect> &srcRect, std::vector<SDL_Rect> &dstRect)
{
    
    int left = objPosX - objWidth/2;
    int top = objPosY - objHeight/2;
    int right = left + objWidth - 1;
    int bottom = top + objHeight - 1;
    
    // entire object fits on screen without wrapping
    if(left >= 0 && right < screenWidth && top >= 0 && bottom < screenHeight){
        srcRect.push_back(SDL_Rect{0, 0, objWidth, objHeight});
        dstRect.push_back(SDL_Rect{left, top, objWidth, objHeight});        
        return;
    }
    // object height is within the screen
    if(top >= 0 && bottom < screenHeight){
        // object wraps on the left side
        if(left < 0){
            srcRect.push_back(SDL_Rect{0, 0, 0-left, objHeight});
            srcRect.push_back(SDL_Rect{0-left, 0, right+1, objHeight});

            dstRect.push_back(SDL_Rect{left+screenWidth, top, 0-left, objHeight});
            dstRect.push_back(SDL_Rect{0, top, right+1, objHeight});
            return;
        }
        // object wraps on the right side
        else{
            srcRect.push_back(SDL_Rect{0, 0, screenWidth-left, objHeight});
            srcRect.push_back(SDL_Rect{screenWidth-left, 0, right-screenWidth+1, objHeight});

            dstRect.push_back(SDL_Rect{left, top, screenWidth-left, objHeight});
            dstRect.push_back(SDL_Rect{0, top, right-screenWidth+1, objHeight});
            return;
        }
    }
    // object width is within the screen
    if(left >= 0 && right < screenWidth){
        // object wraps on the top
        if(top < 0){
            srcRect.push_back(SDL_Rect{0, 0, objWidth, 0-top});
            srcRect.push_back(SDL_Rect{0, 0-top, objWidth, bottom+1});

            dstRect.push_back(SDL_Rect{left, top+screenHeight, objWidth, 0-top});
            dstRect.push_back(SDL_Rect{left, 0, objWidth, bottom+1});
            return;
        }
        // object wraps on the bottom
        else{
            srcRect.push_back(SDL_Rect{0, 0, objWidth, screenHeight-top});
            srcRect.push_back(SDL_Rect{0, screenHeight-top, objWidth, bottom-screenHeight+1});

            dstRect.push_back(SDL_Rect{left, top, objWidth, screenHeight-top});
            dstRect.push_back(SDL_Rect{left, 0, objWidth, bottom-screenHeight+1});
            return;
        }
    }
    // object wraps top left corner
    if(left < 0 && top < 0){
        srcRect.push_back(SDL_Rect{0, 0, 0-left, 0-top});
        srcRect.push_back(SDL_Rect{0, 0-top, 0-left, bottom+1});
        srcRect.push_back(SDL_Rect{0-left, 0, right+1, 0-top});
        srcRect.push_back(SDL_Rect{0-left, 0-top, right+1, bottom+1});

        dstRect.push_back(SDL_Rect{left+screenWidth, top+screenHeight, 0-left, 0-top});
        dstRect.push_back(SDL_Rect{left+screenWidth, 0, 0-left, bottom+1});
        dstRect.push_back(SDL_Rect{0, top+screenHeight, right+1, 0-top});
        dstRect.push_back(SDL_Rect{0, 0, right+1, bottom+1});
        return;
    }
    // object wraps bottom left corner
    if(left < 0 && bottom >= screenHeight){
        srcRect.push_back(SDL_Rect{0, 0, 0-left, screenHeight-top});
        srcRect.push_back(SDL_Rect{0, screenHeight-top, 0-left, bottom-screenHeight+1});
        srcRect.push_back(SDL_Rect{0-left, 0, right+1, screenHeight-top});
        srcRect.push_back(SDL_Rect{0-left, screenHeight-top, right+1, bottom-screenHeight+1});

        dstRect.push_back(SDL_Rect{left+screenWidth, top, 0-left, screenHeight-top});
        dstRect.push_back(SDL_Rect{left+screenWidth, 0, 0-left, bottom-screenHeight+1});
        dstRect.push_back(SDL_Rect{0, top, right+1, screenHeight-top});
        dstRect.push_back(SDL_Rect{0, 0, right+1, bottom-screenHeight+1});
        return;
    }
    // object wraps top right corner
    if(top < 0 && right >= screenWidth){
        srcRect.push_back(SDL_Rect{0, 0, screenWidth-left, 0-top});
        srcRect.push_back(SDL_Rect{0, 0-top, screenWidth-left, bottom+1});
        srcRect.push_back(SDL_Rect{screenWidth-left, 0, right-screenWidth+1, 0-top});
        srcRect.push_back(SDL_Rect{screenWidth-left, 0-top, right-screenWidth+1, bottom+1});

        dstRect.push_back(SDL_Rect{left, top+screenHeight, screenWidth-left, 0-top});
        dstRect.push_back(SDL_Rect{left, 0, screenWidth-left, bottom+1});
        dstRect.push_back(SDL_Rect{0, top+screenHeight, right-screenWidth+1, 0-top});
        dstRect.push_back(SDL_Rect{0, 0, right-screenWidth+1, bottom+1});
        return;
    }
    // object wraps bottom right corner
    if(right >= screenWidth && bottom >= screenHeight){
        srcRect.push_back(SDL_Rect{0, 0, screenWidth-left, screenHeight-top});
        srcRect.push_back(SDL_Rect{0, screenHeight-top, screenWidth-left, bottom-screenHeight+1});
        srcRect.push_back(SDL_Rect{screenWidth-left, 0, right-screenWidth+1, screenHeight-top});
        srcRect.push_back(SDL_Rect{screenWidth-left, screenHeight-top, right-screenWidth+1, bottom-screenHeight+1});

        dstRect.push_back(SDL_Rect{left, top, screenWidth-left, screenHeight-top});
        dstRect.push_back(SDL_Rect{left, 0, screenWidth-left, bottom-screenHeight+1});
        dstRect.push_back(SDL_Rect{0, top, right-screenWidth+1, screenHeight-top});
        dstRect.push_back(SDL_Rect{0, 0, right-screenWidth+1, bottom-screenHeight+1});
        return;
    }            
}
