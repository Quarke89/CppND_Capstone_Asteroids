#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <unordered_map>
#include <utility>

#include "CTexture.h"
#include "GameObject.h"
#include "constants.h"
#include "StaticObject.h"

enum class PauseMenuItem
{
    TITLE,
    PRESS_BUTTON,
    ITEM_TOTAL
};

class MenuPause
{
    public:
        MenuPause(GameObject* backgroundObject);
        ~MenuPause();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        GameState run();     

        void renderItems();

    private:

        SDL_Renderer* _prenderer;
        
        std::unordered_map<PauseMenuItem, CTexture> _textTextureHash;
        std::unordered_map<PauseMenuItem, GameObject*> _textObjectHash;

        GameObject* _backgroundObject;
};

