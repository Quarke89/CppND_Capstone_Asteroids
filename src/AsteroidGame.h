#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <sstream>

#include "CTexture.h"
#include "GameObject.h"
#include "AsteroidObject.h"
#include "constants.h"

#include "MenuMain.h"
#include "MenuGameOver.h"
#include "MenuPause.h"
#include "MenuNext.h"

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

        bool runLevel();
        void cleanupLevel();

        void run();                
        void handleInput(SDL_Event &e);                
                
        void renderObjects();
        void updateObjects();
                        

        void shootLaser();
        void createLaser(Point pos, CVector velocity);

        void checkShipCollision();
        void checkAsteroidCollision();
        void splitAsteroid(AsteroidObject* asteroid);
        void createAsteroid(Point pos, CVector velocity, CTexture* pTex, AsteroidSize size, AsteroidColor color);

        void checkLevelCompleted();
        void levelCompleted();

        void cleanup();
        Point getRandomCorner();
    
        // utlity methods
        std::string getTexturePath(TextureType type);
        bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);

        void runMainMenu();
        void runGameOverMenu();
        void runNextMenu();
        void runPauseMenu();

        void updateScore(int scoreIncrease);
        
    private:

        SDL_Window* _pwindow{nullptr};
        SDL_Renderer* _prenderer{nullptr};

        std::vector<CTexture> _mainTextures;
        std::vector<TTF_Font*> _mainFonts;
        
        GameObject* _pShip{nullptr};
        std::unordered_map<int, GameObject*> _laserHash;
        std::unordered_map<int, GameObject*> _asteroidHash;

        GameState _state;                
        AsteroidColor _currentColor;
        int _currentLevel;
        
        int _score;
        int _lastUpdatedScore;

        CTexture _fontTextureLevel;        
        GameObject* _fontObjectLevel;

        CTexture _fontTextureScore;
        GameObject* _fontObjectScore;

};