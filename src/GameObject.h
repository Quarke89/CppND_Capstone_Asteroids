#pragma once

#include "utility.h"
#include <memory>
#include "CTexture.h"
#include "CVector.h"
#include <vector>


enum class ObjectType
{
    STATIC,
    ASTEROID,
    SHIP,
    LASER
};

class GameObject{

    public:

        GameObject(Point pos, CTexture* pTex);
        GameObject(Point pos, CTexture* pTex, CVector velocity);
        GameObject(Point pos, CTexture* pTex, CVector velocity, double rotation);

        virtual void render(SDL_Renderer* renderer);
        virtual void update(Uint32 updateTime){};
        
        static GameObject* Create(ObjectType type, Point pos, CTexture* tex, CVector velocity=CVector(), double rotation=0);

        // getter functions
        Point getPos();
        CVector getVelocity();
        double getRotation();
        int getID();
        
    protected:

         void calculateRenderRectangles(int objPosX, int objPosY, int objWidth, int objHeight, int screenWidth, int screenHeight, 
                                        std::vector<SDL_Rect> &srcRect, std::vector<SDL_Rect> &dstRect);

        Point _pos;
        CTexture* _pTex;

        CVector _velocity;
        double _rotation;

        Uint32 _lastUpdated;
                        
        int _id;
        static int _count;
};

