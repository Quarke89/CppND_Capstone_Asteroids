#pragma once

#include "Menu.h"


class MenuNext : public Menu
{
    public:

        MenuNext(SDL_Renderer_unique_ptr &renderer, std::unique_ptr<StaticObject> &backgroundObject, std::vector<TTF_Font*> &mainFonts);        
    
    private:

        virtual void initMenuItems();
};
