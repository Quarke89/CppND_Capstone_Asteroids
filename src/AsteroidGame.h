#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "CTexture.h"
#include <memory>
#include <vector>
#include "GameObject.h"
#include <unordered_map>
#include <utility>
#include <vector>

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
    TEX_SHIP,
    TEX_LASER,
    TEX_TOTAL
};

class AsteroidGame{

    public:
        AsteroidGame();
        ~AsteroidGame();

        bool init();
        void run();
        void cleanup();
        
        void handleInput(SDL_Event &e);

        bool loadTextures();
        std::string getTexturePath(TextureType type);

        void initLevel();
        void initShip();
        
        void renderObjects();
        void updateObjects();

        bool checkShipCollision();
        std::vector<int> checkAsteroidCollision();
        bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);

        void createLaser();

        
    private:

        SDL_Window* _pwindow{nullptr};
        SDL_Renderer* _prenderer{nullptr};
        std::vector<CTexture> _mainTextures;

        int _currentLevel;

        GameObject* _pShip;

        std::unordered_map<int, GameObject*> _laserHash;
        std::unordered_map<int, GameObject*> _asteroidHash;

        bool _running;

        

};