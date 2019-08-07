#pragma once

#include <vector>
#include <memory>

#include "CTexture.h"
#include "CVector.h"
#include "utility.h"

class GameObject{

    public:

        GameObject(Point pos, CTexture* pTex);
        GameObject(Point pos, CTexture* pTex, CVector velocity);
        GameObject(Point pos, CTexture* pTex, CVector velocity, double rotation);
        virtual ~GameObject() = default;

        virtual void render(SDL_Renderer* renderer);
        virtual void update(Uint32 updateTime);
        
        static std::unique_ptr<GameObject> Create(ObjectType type, Point pos, CTexture* tex, CVector velocity=CVector(), double rotation=0);

        // getter functions
        Point getPos() const;
        CVector getVelocity() const;
        double getRotation() const;
        int getID() const;
        
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

