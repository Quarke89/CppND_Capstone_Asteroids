#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <unordered_map>
#include <utility>

#include "CTexture.h"
#include "GameObject.h"
#include "GameObjectStatic.h"
#include "constants.h"

enum class MenuItem
{
    TITLE,
    ITEM1,
    ITEM2,
    ITEM1_SELECT,
    ITEM2_SELECT,
    ITEM_TOTAL
};

class Menu
{
    public:
        Menu(SDL_Renderer& renderer, GameObjectStatic& backgroundObject, std::vector<TTF_Font*>& mainFonts);
        virtual ~Menu() = default;

        virtual GameState run();
    
    protected:

        virtual void initMenuItems(){};
        void render();
        virtual void renderMenuItems();

        std::unique_ptr<GameObjectStatic> createStaticTextObject(Point pos, CTexture &tex);

        SDL_Renderer& _renderer;
        GameObjectStatic& _backgroundObject;
        std::vector<TTF_Font*> &_mainFonts;

        std::unordered_map<MenuItem, CTexture> _textTextureHash;
        std::unordered_map<MenuItem, std::unique_ptr<GameObjectStatic>> _textObjectHash;

};

