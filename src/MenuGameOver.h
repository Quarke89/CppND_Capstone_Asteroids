#pragma once

#include "Menu.h"

class MenuGameOver : public Menu
{
    public:

        MenuGameOver(SDL_Renderer_unique_ptr &renderer, std::unique_ptr<StaticObject> &backgroundObject, std::vector<TTF_Font*> &mainFonts);

        virtual GameState run();
    
    private:

        virtual void initMenuItems();
        virtual void renderMenuItems();
        void toggleState(); 
        GameState select();

        bool _state;
};

