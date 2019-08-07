#include "MenuNext.h"

MenuNext::MenuNext(SDL_Renderer_unique_ptr &renderer, std::unique_ptr<StaticObject> &backgroundObject, std::vector<TTF_Font*> &mainFonts)
 :Menu(renderer, backgroundObject, mainFonts)
{
    initMenuItems();
}

void MenuNext::initMenuItems()
{
    SDL_Color whiteTextColor{255,255,255,255};

    const int numItems = 2;

    for(int i = 0; i < numItems; i++){
        _textTextureHash.insert(std::make_pair(static_cast<MenuItem>(i), CTexture()) );
    }

    _textTextureHash[MenuItem::TITLE].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::TITLE2)], "LEVEL COMPLETE", whiteTextColor);
    _textTextureHash[MenuItem::ITEM1].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::MENU)], "Press Enter...", whiteTextColor);

    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH -  _textTextureHash[MenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::TITLE].getHeight())/3)};
    
    Point item1Pos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH -  _textTextureHash[MenuItem::ITEM1].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::ITEM1].getHeight())/2)};

    _textObjectHash[MenuItem::TITLE] = createStaticTextObject(titlePos, _textTextureHash[MenuItem::TITLE]); 
    _textObjectHash[MenuItem::ITEM1] = createStaticTextObject(item1Pos, _textTextureHash[MenuItem::ITEM1]); 

}
