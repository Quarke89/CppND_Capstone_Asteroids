#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "CTexture.h"
#include <memory>
#include <vector>
#include "GameObject.h"

enum class TextureType
{
    TEX_BACKGROUND,
    TEX_ASTEROID_BIG_1,
    TEX_ASTEROID_BIG_2,
    TEX_ASTEROID_BIG_3,
    TEX_ASTEROID_MED_1,
    TEX_ASTEROID_MED_2,
    TEX_ASTEROID_MED_3,
    TEX_ASTEROID_SMALL_1,
    TEX_ASTEROID_SMALL_2,
    TEX_ASTEROID_SMALL_3,
    TEX_TOTAL
};

class AsteroidGame{

    public:
        AsteroidGame();
        ~AsteroidGame();

        bool init();
        void run();
        void cleanup();

        bool loadTextures();
        std::string getTexturePath(TextureType type);

        void initLevel();
        void renderObjects();
        void updateObjects();
        
    private:

        SDL_Window* _pwindow{nullptr};
        SDL_Renderer* _prenderer{nullptr};
        std::vector<CTexture> _mainTextures;

        int _currentLevel;

        std::vector<GameObject*> _gameObjects;
        

};