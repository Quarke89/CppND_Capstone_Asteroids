#include "MenuMain.h"

MenuMain::MenuMain() : _state(true)
{}

MenuMain::~MenuMain()
{}

void MenuMain::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255};
    SDL_Color selectTextColor{245,227,66};


    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(MenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<MenuItem>(i), CTexture()) );
    }
    _textTextureHash[MenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE1)], "Asteroids", whiteTextColor);
    _textTextureHash[MenuItem::PLAY].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Game", whiteTextColor);
    _textTextureHash[MenuItem::QUIT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", whiteTextColor);
    _textTextureHash[MenuItem::PLAY_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Game", selectTextColor);
    _textTextureHash[MenuItem::QUIT_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", selectTextColor);

    
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::TITLE].getHeight())/3)};
    _textObjectHash[MenuItem::TITLE] = GameObject::Create(ObjectType::STATIC, titlePos, &_textTextureHash[MenuItem::TITLE]); 
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MenuItem::PLAY].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::PLAY].getHeight())/2)};
    _textObjectHash[MenuItem::PLAY] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[MenuItem::PLAY]); 
    _textObjectHash[MenuItem::PLAY_SELECT] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[MenuItem::PLAY_SELECT]); 


    Point quitPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[MenuItem::QUIT].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[MenuItem::QUIT].getHeight())/1.8)};
    _textObjectHash[MenuItem::QUIT] = GameObject::Create(ObjectType::STATIC, quitPos, &_textTextureHash[MenuItem::QUIT]); 
    _textObjectHash[MenuItem::QUIT_SELECT] = GameObject::Create(ObjectType::STATIC, quitPos, &_textTextureHash[MenuItem::QUIT_SELECT]); 

}

void MenuMain::run()
{
    bool quit = false;
    SDL_Event event;

    while(!quit){

        while( SDL_PollEvent( &event ) != 0 ) {            
            if( event.type == SDL_QUIT ){
                quit = true;
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_s:
                        toggleState();
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear(_prenderer);

        _textObjectHash[MenuItem::TITLE]->render(_prenderer);
        if(_state){
            _textObjectHash[MenuItem::PLAY_SELECT]->render(_prenderer);
            _textObjectHash[MenuItem::QUIT]->render(_prenderer);
        }
        else{
            _textObjectHash[MenuItem::PLAY]->render(_prenderer);
            _textObjectHash[MenuItem::QUIT_SELECT]->render(_prenderer);
        }
        
        
        SDL_RenderPresent(_prenderer);
    }
}

void MenuMain::toggleState()
{
    _state = !_state;
}
