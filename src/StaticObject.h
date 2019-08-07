#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
    public:

        StaticObject(Point pos, CTexture* tex);

        virtual void render(SDL_Renderer* renderer, SDL_Rect* dest = nullptr);


    private:

};