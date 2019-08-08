#pragma once

#include "GameObject.h"
#include <vector>

class AsteroidObject : public GameObject
{

    public:
        AsteroidObject(const Point& pos, const CTexture& tex, CVector velocity);
        
        void render(SDL_Renderer& renderer) override;
        void update(const Uint32 updateTime) override;
        
        std::vector<SDL_Rect>& getBoundingBoxes();

        AsteroidSize getSize() const;
        AsteroidSize getNextSize() const;

        void setAsteroidAttr(AsteroidSize size, AsteroidColor color);
        
        static AsteroidColor getNextColor(AsteroidColor color);
        static TextureType getAsteroidTexture(AsteroidSize size, AsteroidColor color);

    private:
        
        // calculate offscreen wrap arounds for textures
        void calculateRenderRectangles(int objPosX, int objPosY, int objWidth, int objHeight, int screenWidth, int screenHeight, 
                                        std::vector<SDL_Rect> &srcRect, std::vector<SDL_Rect> &dstRect);

        AsteroidSize _asteroidSize;
        AsteroidColor _asteroidColor;

        std::vector<SDL_Rect> _boundingBoxes;
};