#pragma once

#include "GameObject.h"

class LaserObject : public GameObject
{
    public:

        LaserObject(Point pos, CTexture* tex, CVector velocity, double rotation) ;

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer_unique_ptr &renderer);

        SDL_Rect& getBoundingBox();

        bool checkOffscreen();

    private:

        int _width;
        int _height;
        SDL_Rect _boundingBox;
};