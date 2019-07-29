#pragma once

#include "utility.h"
#include <memory>
#include "CTexture.h"
#include "AsteroidObject.h"



enum class ObjectType
{
    BACKGROUND_IMG,
    ASTEROID,
    SHIP
};

class GameObject{

    public:

        GameObject(){}
        
        static GameObject* Create(ObjectType type);




    private:

        Position _pos;
        std::shared_ptr<CTexture> _pTex;


};