#pragma once

#include "Menu.h"


class MenuPause : public Menu
{
    public:

        MenuPause(SDL_Renderer& renderer, GameObjectStatic& backgroundObject, std::vector<TTF_Font*>& mainFonts);
    
    private:

        virtual void initMenuItems();
};

