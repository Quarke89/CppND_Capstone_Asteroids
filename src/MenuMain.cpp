#include "MenuMain.h"

MenuMain::MenuMain(StaticObject* backgroundObject) : _state(true), _backgroundObject(backgroundObject)
{}

MenuMain::~MenuMain()
{}

void MenuMain::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255,255};
    SDL_Color selectTextColor{245,227,66,255};


    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(MainMenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<MainMenuItem>(i), CTexture()) );
    }
    _textTextureHash[MainMenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE1)], "Asteroids", whiteTextColor);
    _textTextureHash[MainMenuItem::PLAY].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Game", whiteTextColor);
    _textTextureHash[MainMenuItem::QUIT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", whiteTextColor);
    _textTextureHash[MainMenuItem::PLAY_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Game", selectTextColor);
    _textTextureHash[MainMenuItem::QUIT_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", selectTextColor);
    
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MainMenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MainMenuItem::TITLE].getHeight())/3)};
     
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MainMenuItem::PLAY].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MainMenuItem::PLAY].getHeight())/2)};

    Point quitPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MainMenuItem::QUIT].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MainMenuItem::QUIT].getHeight())/1.8)};


    _textObjectHash[MainMenuItem::TITLE] = createStaticTextObject(titlePos, &_textTextureHash[MainMenuItem::TITLE]);
    _textObjectHash[MainMenuItem::PLAY] = createStaticTextObject(playPos, &_textTextureHash[MainMenuItem::PLAY]); 
    _textObjectHash[MainMenuItem::PLAY_SELECT] = createStaticTextObject(playPos, &_textTextureHash[MainMenuItem::PLAY_SELECT]); 
    _textObjectHash[MainMenuItem::QUIT] = createStaticTextObject(quitPos, &_textTextureHash[MainMenuItem::QUIT]); 
    _textObjectHash[MainMenuItem::QUIT_SELECT] = createStaticTextObject(quitPos, &_textTextureHash[MainMenuItem::QUIT_SELECT]); 

}

std::unique_ptr<StaticObject> MenuMain::createStaticTextObject(Point pos, CTexture* pTex)
{
    std::unique_ptr<GameObject> pGO = GameObject::Create(ObjectType::STATIC, pos, pTex); 
    return static_unique_ptr_cast<StaticObject, GameObject>(std::move(pGO));

}

GameState MenuMain::run()
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

        renderItems();
        
    }
}

        
void MenuMain::renderItems()
{
    SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(_prenderer);

    SDL_Rect backgroundRect{0,0,AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT};
    static_cast<StaticObject*>(_backgroundObject)->render(_prenderer, &backgroundRect);

    _textObjectHash[MainMenuItem::TITLE]->render(_prenderer);
    if(_state){
        _textObjectHash[MainMenuItem::PLAY_SELECT]->render(_prenderer);
        _textObjectHash[MainMenuItem::QUIT]->render(_prenderer);
    }
    else{
        _textObjectHash[MainMenuItem::PLAY]->render(_prenderer);
        _textObjectHash[MainMenuItem::QUIT_SELECT]->render(_prenderer);
    }
    
    SDL_RenderPresent(_prenderer);

}

void MenuMain::toggleState()
{
    _state = !_state;
}

GameState MenuMain::select()
{
    if(_state){
        return GameState::RUNNING;
    }
    else{
        return GameState::QUIT;
    }
}
