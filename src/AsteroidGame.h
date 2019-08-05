#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <vector>

#include "CTexture.h"
#include "GameObject.h"
#include "AsteroidObject.h"
#include "constants.h"

#include "MenuMain.h"


class AsteroidGame{

    public:
        AsteroidGame();
        ~AsteroidGame();

        // init methods
        bool init();
        void initLevel();
        void initShip();
        bool loadTextures();
        bool loadFonts();

        void run();                
        void handleInput(SDL_Event &e);                
                
        void renderObjects();
        void updateObjects();
                        

        void shootLaser();
        void createLaser(Point pos, CVector velocity);

        bool checkShipCollision();
        void checkAsteroidCollision();
        void splitAsteroid(AsteroidObject* asteroid);
        void createAsteroid(Point pos, CVector velocity, CTexture* pTex, AsteroidSize size, AsteroidColor color);

        void cleanup();

        // utlity methods
        std::string getTexturePath(TextureType type);
        bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
        
    private:

        SDL_Window* _pwindow{nullptr};
        SDL_Renderer* _prenderer{nullptr};

        std::vector<CTexture> _mainTextures;
        std::vector<TTF_Font*> _mainFonts;
        
        GameObject* _pShip{nullptr};

        std::unordered_map<int, GameObject*> _laserHash;
        std::unordered_map<int, GameObject*> _asteroidHash;

        bool _running;
        int _currentLevel;

        AsteroidColor _currentColor;

        MenuMain _mainmenu;

};