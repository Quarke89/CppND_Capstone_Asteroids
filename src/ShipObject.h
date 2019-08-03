#pragma once

#include "GameObject.h"
#include <vector>

class ShipObject : public GameObject
{
    public:

        ShipObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);

    private:

        std::vector<SDL_Rect> _boundingBoxs;
};