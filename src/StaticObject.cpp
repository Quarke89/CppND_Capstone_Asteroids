/* File:            StaticObject.cpp
 * Author:          Vish Potnis
 * Description:     - Derived class for static objects (text and background)
 *                  - Only render function is overriden
 */

#include "StaticObject.h"

// basic constructor that accepts position and texture of the object
StaticObject::StaticObject(const Point& pos, const CTexture& tex)
    : GameObject(pos, tex)
{}

// render object to screen, destination rectangle is size of texture
void StaticObject::render(SDL_Renderer& renderer) 
{
    SDL_Rect renderQuad{static_cast<int>(_pos.x), static_cast<int>(_pos.y), _tex.getWidth(), _tex.getHeight()};
    SDL_RenderCopy( &renderer, &_tex.getTexture(), nullptr, &renderQuad);    
}

// render object to screen, destination is given by dest
void StaticObject::render(SDL_Renderer& renderer, SDL_Rect& dest) const
{
    SDL_RenderCopy( &renderer, &_tex.getTexture(), nullptr, &dest);    
}