#pragma once

#include <SDL2/SDL.h>

using SDL_Window_unique_ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDL_Renderer_unique_ptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using SDL_Texture_unique_ptr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

template<typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast( std::unique_ptr<Base>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived>(d);
}

enum class MenuItem
{
    TITLE,
    ITEM1,
    ITEM2,
    ITEM1_SELECT,
    ITEM2_SELECT,
    ITEM_TOTAL
};

struct Point{
    double x;
    double y;
};

enum class GameState
{
    QUIT,
    LEVEL_COMPLETE,
    GAMEOVER,
    RUNNING,
    PLAY_AGAIN
};

enum class ObjectType
{
    STATIC,
    ASTEROID,
    SHIP,
    LASER,
    EXPLOSION
};

enum class AsteroidSize
{
    BIG,
    MED,
    SMALL
};
enum class AsteroidColor
{
    GREY,
    RED,
    BROWN
};

enum class FontType
{
    TITLE1,
    TITLE2,
    MENU,
    TEXT,
    FONT_TOTAL
};

enum class TextureType
{    
    TEX_ASTEROID_BIG_1,
    TEX_ASTEROID_MED_1,
    TEX_ASTEROID_SMALL_1,
    TEX_ASTEROID_BIG_2,
    TEX_ASTEROID_MED_2,
    TEX_ASTEROID_SMALL_2,
    TEX_ASTEROID_BIG_3,
    TEX_ASTEROID_MED_3,
    TEX_ASTEROID_SMALL_3,
    TEX_SHIP,
    TEX_LASER,
    TEX_BACKGROUND,
    TEX_EXPLOSION_SPRITE_SHEET,
    TEX_TOTAL
};