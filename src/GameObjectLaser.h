#pragma once

#include "GameObject.h"

class GameObjectLaser : public GameObject
{
    public:

        GameObjectLaser(const Point& pos, const CTexture& tex, CVector velocity, double rotation) ;

        void render(SDL_Renderer &renderer) override;
        void update(const Uint32 updateTime) override;
        

        SDL_Rect& getBoundingBox();

        bool checkOffscreen() const;

    private:

        int _width;
        int _height;
        SDL_Rect _boundingBox;
};