#pragma once

#include "GameObject.h"
#include <vector>


class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);
        
        std::vector<SDL_Rect>& getBoundingBoxes();

    private:
   
        void renderBoxes(SDL_Renderer* renderer);
        int _numTex;
        std::vector<SDL_Rect> _boundingBoxes;


};