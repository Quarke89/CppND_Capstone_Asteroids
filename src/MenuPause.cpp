#include "MenuPause.h"

MenuPause::MenuPause(StaticObject* backgroundObject) :_backgroundObject(backgroundObject)
{}

MenuPause::~MenuPause()
{}

void MenuPause::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255,255};

    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(PauseMenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<PauseMenuItem>(i), CTexture()) );
    }
    _textTextureHash[PauseMenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE2)], "Paused", whiteTextColor);
    _textTextureHash[PauseMenuItem::PRESS_BUTTON].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Press Enter...", whiteTextColor);
   
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[PauseMenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[PauseMenuItem::TITLE].getHeight())/3)};
     
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[PauseMenuItem::PRESS_BUTTON].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[PauseMenuItem::PRESS_BUTTON].getHeight())/2)};

    _textObjectHash[PauseMenuItem::TITLE] = createStaticTextObject(titlePos, &_textTextureHash[PauseMenuItem::TITLE]); 
    _textObjectHash[PauseMenuItem::PRESS_BUTTON] = createStaticTextObject(playPos, &_textTextureHash[PauseMenuItem::PRESS_BUTTON]); 

}

std::unique_ptr<StaticObject> MenuPause::createStaticTextObject(Point pos, CTexture* pTex)
{
    std::unique_ptr<GameObject> pGO = GameObject::Create(ObjectType::STATIC, pos, pTex); 
    return static_unique_ptr_cast<StaticObject, GameObject>(std::move(pGO));
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
