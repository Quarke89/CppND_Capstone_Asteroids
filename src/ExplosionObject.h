/* File:            ExplosionObject.h
 * Author:          Vish Potnis
 * Description:     - Derived class for explosion objects 
 *                  - Render animation sprites over time
 */

#pragma once

#include "GameObject.h"
#include "constants.h"
#include "utility.h"

class ExplosionObject : public GameObject
{
    public:

        ExplosionObject(const Point& pos, const CTexture& tex);     // constructor that accepts position and texture of the object

        void render(SDL_Renderer& renderer) override;         // render object to screen
        void update(const Uint32 updateTime) override;              // update animation frame based on timer
        

        void setSize(AsteroidSize size);
        bool isAnimationDone() const;

    private:

        static std::vector<SDL_Rect> _spriteClips;
        int _width;
        int _height;
        int _currentClip;
};