/* File:            AsteroidGame.h
 * Author:          Vish Potnis
 * Description:     - Parent class for the game
 *                  - Contains main game loop
 *                  - Handle input events
 *                  - Create and manage game onjects
 */

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
#include <string>
#include <sstream>
#include <random>

#include "constants.h"
#include "utility.h"
#include "CTexture.h"
#include "GameObject.h"
#include "AsteroidObject.h"
#include "ShipObject.h"
#include "LaserObject.h"
#include "ExplosionObject.h"
#include "StaticObject.h"

#include "MenuMain.h"
#include "MenuGameOver.h"
#include "MenuPause.h"
#include "MenuNext.h"

class AsteroidGame{

    public:
        AsteroidGame();
        ~AsteroidGame();

        // top level call to run the game
        void run();                

    private:

        //////////// Private functions ///////////////

        bool init();                                    // initialize SDL assets
        bool loadFonts();                               // load fonts with SDL_ttf
        bool loadTextures();                            // load sprites into texture objects
        std::string getTexturePath(TextureType type);   // utility function for getting file paths

        void runLevel();                    // main game loop

        void handleInput(SDL_Event &e);     // handle keyboard input             
        void renderObjects();               // render all active game objects
        void updateObjects();               // update all non-static game objects based on time delta

        void initLevel();                   // initialize level with asteroids and ship based on current level

        // wrappers for static factory method for creating game objects
        void createShip();
        void createLaser(Point pos, CVector velocity);
        void createAsteroid(Point pos, CVector velocity, CTexture* pTex, AsteroidSize size, AsteroidColor color);
        void createExplosion(Point pos, AsteroidSize size);

        void checkShipCollision();                                  // check ship <-> asteroid collision
        void checkAsteroidCollision();                              // check laser <-> asteroid collision
        bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);  // check collision between 2 SDL_Rect bounding boxes

        void shootLaser();                              // determine velocity vector to create laser after keyboard input
        void splitAsteroid(AsteroidObject* asteroid);   // split current asteroid into 2 smaller asteroid

        void checkLevelCompleted();         // check if any asteroids are remaining in the level

        void cleanupLevel();                    // clean up game objects
        void cleanup();                         // clean up textures and SDL assets

        Point getRandomCorner();                    // utility function for determining initial position for asteroids
        void updateScore(int scoreIncrease);        // update score and regenerate score texture

        void runMainMenu();                         // display the main menu
        void runGameOverMenu();                     // display the game over menu
        void runNextMenu();                         // display the next level menu
        void runPauseMenu();                        // display the pause menu

        ////////// Private variables //////////////

        SDL_Window* _pwindow{nullptr};          // pointer to the main game window
        SDL_Renderer* _prenderer{nullptr};      // pointer to the GPU renderer

        std::vector<CTexture> _mainTextures;    // vector holding the main loaded textures
        std::vector<TTF_Font*> _mainFonts;      // vector holding the fonts converted by SDL_TTF
        
        GameObject* _pShip{nullptr};                            // Game object for the ship
        std::unordered_map<int, GameObject*> _laserHash;        // Hashmap for active laser objects with a unique ID as the key
        std::unordered_map<int, GameObject*> _asteroidHash;     // Hashmap for active asteroid objects with a unique ID as the key
        std::unordered_map<int, GameObject*> _explosionHash;    // Hashmap for active explosion objects with a unique ID as the key
        GameObject* _backgroundObject;                          // Game object for the background image

        GameState _state;                   // Game state enum 
        AsteroidColor _currentColor;        // Asteroid color enum, determines color for current level

        int _currentLevel;
        int _score;

        CTexture _fontTextureLevel;         // loaded font to display level
        GameObject* _fontObjectLevel;       // loaded texture/object to display level

        CTexture _fontTextureScore;         // loaded font to display score
        GameObject* _fontObjectScore;       // loaded texture/object to display score

};