#include "MenuGameOver.h"

MenuGameOver::MenuGameOver(SDL_Renderer& renderer, StaticObject& backgroundObject, std::vector<TTF_Font*>& mainFonts)
 : Menu(renderer, backgroundObject, mainFonts), _state(true)
{
    initMenuItems();
}

GameState MenuGameOver::run()
{
    SDL_Event event;

    while(true){

        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                return GameState::QUIT;
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_s:
                    case SDLK_UP:
                    case SDLK_DOWN:
                        toggleState();
                        break;
                    case SDLK_RETURN:
                        return select();
                        break;
                    default:
                        break;
                }
            }
        }

        render();
    }
}

void MenuGameOver::initMenuItems()
{
    SDL_Color whiteTextColor{255,255,255,255};
    SDL_Color selectTextColor{245,227,66,255};

    const int numItems = 5;

    for(int i = 0; i < numItems; i++){
        _textTextureHash.insert(std::make_pair(static_cast<MenuItem>(i), CTexture()) );
    }

    _textTextureHash[MenuItem::TITLE].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::TITLE2)], "GAME OVER", whiteTextColor);
    _textTextureHash[MenuItem::ITEM1].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::MENU)], "Play Again", whiteTextColor);
    _textTextureHash[MenuItem::ITEM2].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::MENU)], "Quit", whiteTextColor);
    _textTextureHash[MenuItem::ITEM1_SELECT].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::MENU)], "Play Again", selectTextColor);
    _textTextureHash[MenuItem::ITEM2_SELECT].loadFromRenderedText(_renderer, _mainFonts[static_cast<int>(FontType::MENU)], "Quit", selectTextColor);

    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH -  _textTextureHash[MenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::TITLE].getHeight())/3)};
    
    Point item1Pos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH -  _textTextureHash[MenuItem::ITEM1].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::ITEM1].getHeight())/2)};

    Point item2Pos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MenuItem::ITEM2].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::ITEM2].getHeight())/1.8)};

    _textObjectHash[MenuItem::TITLE] = createStaticTextObject(titlePos, _textTextureHash[MenuItem::TITLE]); 
    _textObjectHash[MenuItem::ITEM1] = createStaticTextObject(item1Pos, _textTextureHash[MenuItem::ITEM1]);
    _textObjectHash[MenuItem::ITEM2] = createStaticTextObject(item2Pos, _textTextureHash[MenuItem::ITEM2]);
    _textObjectHash[MenuItem::ITEM1_SELECT] = createStaticTextObject(item1Pos, _textTextureHash[MenuItem::ITEM1_SELECT]);
    _textObjectHash[MenuItem::ITEM2_SELECT] = createStaticTextObject(item2Pos, _textTextureHash[MenuItem::ITEM2_SELECT]);

}

void MenuGameOver::renderMenuItems()
{
    
    _textObjectHash[MenuItem::TITLE]->render(_renderer);
    if(_state){
        _textObjectHash[MenuItem::ITEM1_SELECT]->render(_renderer);
        _textObjectHash[MenuItem::ITEM2]->render(_renderer);
    }
    else{
        _textObjectHash[MenuItem::ITEM1]->render(_renderer);
        _textObjectHash[MenuItem::ITEM2_SELECT]->render(_renderer);
    }
}

void MenuGameOver::toggleState()
{
    _state = !_state;
}

GameState MenuGameOver::select()
{
    if(_state){
        return GameState::RUNNING;
    }
    else{
        return GameState::QUIT;
    }
}

