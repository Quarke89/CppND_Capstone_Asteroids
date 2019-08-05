#pragma once

#include "GameObject.h"
#include <vector>

enum class AsteroidType
{
    BIG,
    MED,
    SMALL
};

class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(Point pos, CTexture* tex, CVector velocity, CVector acceleration, Uint32 updateTime);

        virtual void update(Uint32 updateTime);
        virtual void render(SDL_Renderer* renderer);
        
        std::vector<SDL_Rect>& getBoundingBoxes();

        AsteroidType getType();
        TextureType getTexType();

    private:
   
        
        void renderBoxes(SDL_Renderer* renderer);
        AsteroidType _type;
        TextureType _texType;

        AsteroidType texture2asteroid(TextureType type);

        int _numTex;
        std::vector<SDL_Rect> _boundingBoxes;


};