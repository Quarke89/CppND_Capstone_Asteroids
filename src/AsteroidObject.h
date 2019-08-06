#pragma once

#include "GameObject.h"
#include <vector>

class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(Point pos, CTexture* tex, CVector velocity);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);
        
        std::vector<SDL_Rect>& getBoundingBoxes();

        AsteroidSize getSize();
        AsteroidSize getNextSize();
        void setAsteroidAttr(AsteroidSize size, AsteroidColor color);
        static AsteroidColor getNextColor(AsteroidColor color);
        static TextureType getAsteroidTexture(AsteroidSize size, AsteroidColor color);

    private:
        
        void renderBoxes(SDL_Renderer* renderer);

        AsteroidSize _asteroidSize;
        AsteroidColor _asteroidColor;

        std::vector<SDL_Rect> _boundingBoxes;
};