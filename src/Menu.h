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

class Menu
{
    public:
        Menu(GameObject* backgroundObject, SDL_Renderer& renderer, std::vector<TTF_Font*> &mainFonts);
        virtual ~Menu() = default;

};