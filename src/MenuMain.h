#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CTexture.h"
#include <vector>
#include "GameObject.h"
#include "StaticObject.h"
#include <unordered_map>
#include <utility>
#include "constants.h"

enum class MainMenuItem
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
        MenuMain(GameObject* backgroundObject);
        ~MenuMain();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        GameState run();     

        void renderItems();

        void toggleState(); 
        GameState select();

    private:

        SDL_Renderer* _prenderer;
        
        bool _state;

        std::unordered_map<MainMenuItem, CTexture> _textTextureHash;
        std::unordered_map<MainMenuItem, GameObject*> _textObjectHash;

        GameObject* _backgroundObject;

};

