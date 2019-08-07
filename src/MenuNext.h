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

enum class NextMenuItem
{
    TITLE,
    PRESS_BUTTON,
    ITEM_TOTAL
};

class MenuNext
{
    public:
        MenuNext(GameObject* backgroundObject);
        ~MenuNext();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        GameState run();     

        void renderItems();

    private:

        SDL_Renderer* _prenderer;
        
        std::unordered_map<NextMenuItem, CTexture> _textTextureHash;
        std::unordered_map<NextMenuItem, GameObject*> _textObjectHash;

        GameObject* _backgroundObject;
};

