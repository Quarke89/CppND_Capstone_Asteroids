#pragma once

#include "Menu.h"

class MenuGameOver : public Menu
{
    public:

        MenuGameOver(SDL_Renderer& renderer, StaticObject& backgroundObject, std::vector<TTF_Font*>& mainFonts);

        virtual GameState run();
    
    private:

        virtual void initMenuItems();
        virtual void renderMenuItems();
        void toggleState(); 
        GameState select();

        bool _state;
};

