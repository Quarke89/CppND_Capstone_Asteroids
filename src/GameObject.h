#pragma once

#include "utility.h"
#include <memory>
#include "CTexture.h"
#include "CVector.h"


enum class ObjectType
{
    BACKGROUND_IMG,
    ASTEROID,
    SHIP
};

class GameObject{

    public:

        GameObject(Point pos, CTexture* pTex, CVector velocity, CVector acceleration);

        virtual void render(SDL_Renderer* renderer);
        virtual void update(Uint32 updateTime){};
        
        static GameObject* Create(Point pos, ObjectType type, CTexture* tex, CVector velocity, CVector acceleration);

    protected:

        Point _pos;
        CVector _velocity;
        CVector _acceleration;
        double _rotation;
        Uint32 _lastUpdated{0};
        CTexture* _pTex;


};

