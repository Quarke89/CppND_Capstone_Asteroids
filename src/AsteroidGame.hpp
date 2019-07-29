#pragma once

#include <SDL.h>

class AsteroidGame{

public:
    AsteroidGame();
    ~AsteroidGame();

    bool init();
    void run();
    void cleanup();
    

private:

    SDL_Window* _window{nullptr};
    SDL_Renderer* _renderer{nullptr};
    SDL_Surface* _screenSurface{nullptr};


    static constexpr int _SCREEN_WIDTH{800};
    static constexpr int _SCREEN_HEIGHT{600};



};