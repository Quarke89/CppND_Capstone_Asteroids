#pragma once

#include "GameObject.h"
#include "constants.h"
#include "utility.h"

class ExplosionObject : public GameObject
{
    public:

        ExplosionObject(Point pos, CTexture* tex);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);

        void setSize(AsteroidSize size);
        bool isAnimationDone();

    private:

        static std::vector<SDL_Rect> _spriteClips;
        int _width;
        int _height;
        int _currentClip;
};