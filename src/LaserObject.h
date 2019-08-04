#pragma once

#include "GameObject.h"
#include <vector>

class LaserObject : public GameObject
{
    public:

        LaserObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime, double rotation) ;

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);

        SDL_Rect& getBoundingBox();

        bool checkOffscreen();

    private:

        int _width;
        int _height;
        SDL_Rect _boundingBox;
        double _directionAngle;
};