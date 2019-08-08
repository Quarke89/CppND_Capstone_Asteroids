#pragma once

#include "Menu.h"


class MenuNext : public Menu
{
    public:

        MenuNext(SDL_Renderer& renderer, GameObjectStatic& backgroundObject, std::vector<TTF_Font*>& mainFonts);        
    
    private:

        virtual void initMenuItems();
};
