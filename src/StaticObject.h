#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
    public:

        StaticObject(Point pos, CTexture* tex);

        virtual void render(SDL_Renderer_unique_ptr &renderer);
        void render(SDL_Renderer_unique_ptr &renderer, SDL_Rect* dest);


    private:

};