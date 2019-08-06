#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CTexture.h"
#include <vector>
#include "GameObject.h"
#include <unordered_map>
#include <utility>

enum class MenuItem
{
    TITLE,
    PLAY,
    QUIT,
    PLAY_SELECT,
    QUIT_SELECT,
    ITEM_TOTAL
};

class MenuMain
{
    public:
        MenuMain();
        ~MenuMain();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        void run();       
        void toggleState(); 

    private:

        SDL_Renderer* _prenderer;
        
        bool _state;

        std::unordered_map<MenuItem, CTexture> _textTextureHash;
        std::unordered_map<MenuItem, GameObject*> _textObjectHash;
};

