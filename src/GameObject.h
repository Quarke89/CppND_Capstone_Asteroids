#pragma once

#include "utility.h"
#include <memory>
#include "CTexture.h"


enum class ObjectType
{
    BACKGROUND_IMG,
    ASTEROID,
    SHIP
};

class GameObject{

    public:

        GameObject();

        void render(SDL_Renderer* renderer);
        virtual void update(Uint32 updateTime){};
        
        static GameObject* Create(ObjectType type, CTexture* tex);

    


    protected:

        Point _pos{0,0};
        double _velocity{0};
        double _acceleration{0};
        double _rotation{0};
        Uint32 _lastUpdated{0};
        CTexture* _pTex;


};

