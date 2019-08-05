#pragma once

#include "utility.h"
#include <memory>
#include "CTexture.h"
#include "CVector.h"
#include <vector>


enum class ObjectType
{
    BACKGROUND_IMG,
    ASTEROID,
    SHIP,
    LASER
};

class GameObject{

    public:

        GameObject(Point pos, CTexture* pTex, CVector velocity, CVector acceleration, Uint32 updateTime);

        virtual void render(SDL_Renderer* renderer);
        virtual void update(Uint32 updateTime){};
        
        static GameObject* Create(Point pos, ObjectType type, CTexture* tex, CVector velocity, CVector acceleration,  Uint32 updateTime, double rotation=0);

        Point getPos();
        double getRotation();
        int getID();
        CVector getVelocity();

    protected:

         void calculateRenderRectangles(int objPosX, int objPosY, int objWidth, int objHeight, int screenWidth, int screenHeight, 
                                        std::vector<SDL_Rect> &srcRect, std::vector<SDL_Rect> &dstRect);

        Point _pos;
        CVector _velocity;
        CVector _acceleration;
        double _rotation;
        Uint32 _lastUpdated;
        CTexture* _pTex;
        int _id;

        static int _count;


};

