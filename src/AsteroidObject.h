#pragma once

#include "GameObject.h"
#include <vector>

class GameObject;

class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);

    private:

        void calculateRenderRectangles(int objPosX, int objPosY, int objWidth, int objHeight, int screenWidth, int screenHeight, 
                                        std::vector<SDL_Rect> &srcRect, std::vector<SDL_Rect> &dstRect);
        void renderBoxes(SDL_Renderer* renderer);
        int _numTex;
        std::vector<SDL_Rect> _boundingBoxs;


};