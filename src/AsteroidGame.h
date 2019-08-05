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
#include "AsteroidObject.h"



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
        void checkAsteroidCollision();
        bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);

        void shootLaser();
        void createLaser(Point pos, CVector velocity);

        void splitAsteroid(AsteroidObject* asteroid);
        void createAsteroid(Point pos, CVector velocity, CTexture* pTex);

        
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