#include "GameObject.h"
#include "AsteroidObject.h"
#include "ShipObject.h"
#include "LaserObject.h"


GameObject::GameObject(Point pos, CTexture* pTex, CVector velocity, CVector acceleration)
    :_pos(pos), _pTex(pTex), _velocity(velocity), _acceleration(acceleration), _lastUpdated(0)
{}

GameObject* GameObject::Create(Point pos, ObjectType type, CTexture* tex, CVector velocity, CVector acceleration, double rotation)
{
    switch(type){
        case ObjectType::ASTEROID: return new AsteroidObject(pos, tex, velocity, acceleration);
        case ObjectType::SHIP: return new ShipObject(pos, tex, velocity, acceleration);
        case ObjectType::LASER: return new LaserObject(pos, tex, velocity, acceleration, rotation);
        default: 
            return nullptr;

    }
}

Point GameObject::getPos()
{
    return _pos;
}

double GameObject::getRotation()
{
    return _rotation;
}

void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _pTex->getWidth(), _pTex->getHeight()};
    SDL_RenderCopy( renderer, _pTex->getTexture(), NULL, &renderQuad );    

}

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
