
#pragma once 

enum class GameState
{
    QUIT,
    LEVEL_COMPLETE,
    GAMEOVER,
    RUNNING,
    PLAY_AGAIN
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
    TEX_TOTAL
};

namespace AsteroidConstants
{
    constexpr int SCREEN_WIDTH{800};
    constexpr int SCREEN_HEIGHT{600};        
    constexpr double PI{3.14159265};

    constexpr int INIT_ASTEROID_VELOCITY{100};
    constexpr double ASTEROID_VELOCITY_MULTIPLIER{1.1};
    constexpr int LASER_VELOCITY{500};

    constexpr int OFFSCREEN_BOUNDARY{50};

    constexpr int FONTSIZE_TITLE1{100};
    constexpr int FONTSIZE_TITLE2{64};
    constexpr int FONTSIZE_MENU{32};
    constexpr int FONTSIZE_TEXT{24};

    constexpr double SCALE_SHIP_W{1.5};
    constexpr double SCALE_SHIP_H{1.5};
    constexpr double SCALE_LASER_W{20};
    constexpr double SCALE_LASER_H{24};



} 
