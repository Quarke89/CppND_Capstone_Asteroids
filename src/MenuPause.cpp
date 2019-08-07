#include "MenuPause.h"

MenuPause::MenuPause(GameObject* backgroundObject) :_backgroundObject(backgroundObject)
{}

MenuPause::~MenuPause()
{}

void MenuPause::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255};
    SDL_Color selectTextColor{245,227,66};

    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(PauseMenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<PauseMenuItem>(i), CTexture()) );
    }
    _textTextureHash[PauseMenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE2)], "Paused", whiteTextColor);
    _textTextureHash[PauseMenuItem::PRESS_BUTTON].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Press Enter...", whiteTextColor);
   
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[PauseMenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[PauseMenuItem::TITLE].getHeight())/3)};
    _textObjectHash[PauseMenuItem::TITLE] = GameObject::Create(ObjectType::STATIC, titlePos, &_textTextureHash[PauseMenuItem::TITLE]); 
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[PauseMenuItem::PRESS_BUTTON].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[PauseMenuItem::PRESS_BUTTON].getHeight())/2)};
    _textObjectHash[PauseMenuItem::PRESS_BUTTON] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[PauseMenuItem::PRESS_BUTTON]); 

}

GameState MenuPause::run()
{
    SDL_Event event;

    while(true){

        while( SDL_PollEvent( &event ) != 0 ) {            
            if( event.type == SDL_QUIT ){
                return GameState::QUIT;
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        return GameState::RUNNING;
                        break;
                    default:
                        break;
                }
            }
        }

        renderItems();
        
    }
}
        
void MenuPause::renderItems()
{
    SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(_prenderer);

    SDL_Rect backgroundRect{0,0,AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT};
    static_cast<StaticObject*>(_backgroundObject)->render(_prenderer, &backgroundRect);

    _textObjectHash[PauseMenuItem::TITLE]->render(_prenderer);
    _textObjectHash[PauseMenuItem::PRESS_BUTTON]->render(_prenderer);
    
    SDL_RenderPresent(_prenderer);

}
