#pragma once

#include "GameObject.h"

class GameObject;

class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(CTexture* tex);

        virtual void update(Uint32 updateTime);

    private:

};