#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "CTexture.h"
#include <vector>
#include "GameObject.h"
#include <unordered_map>
#include <utility>
#include "constants.h"
#include "StaticObject.h"

enum class GameOverMenuItem
{
    TITLE,
    PLAY_AGAIN,
    QUIT,
    PLAY_AGAIN_SELECT,
    QUIT_SELECT,
    ITEM_TOTAL
};

class MenuGameOver
{
    public:
        MenuGameOver(StaticObject* backgroundObject);
        ~MenuGameOver();

        void init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts);
        GameState run();     

        void renderItems();

        void toggleState(); 
        GameState select();

    private:

        std::unique_ptr<StaticObject> createStaticTextObject(Point pos, CTexture* pTex);
        
        SDL_Renderer* _prenderer;
        
        bool _state;

        std::unordered_map<GameOverMenuItem, CTexture> _textTextureHash;
        std::unordered_map<GameOverMenuItem, std::unique_ptr<StaticObject>> _textObjectHash;

        StaticObject* _backgroundObject;
};

