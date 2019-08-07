#include "MenuGameOver.h"

MenuGameOver::MenuGameOver(GameObject* backgroundObject) : _state(true), _backgroundObject(backgroundObject)
{}

MenuGameOver::~MenuGameOver()
{}

void MenuGameOver::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color whiteTextColor{255,255,255,255};
    SDL_Color selectTextColor{245,227,66,255};

    _prenderer = renderer;

    for(int i = 0; i < static_cast<int>(GameOverMenuItem::ITEM_TOTAL); i++){
        _textTextureHash.insert(std::make_pair(static_cast<GameOverMenuItem>(i), CTexture()) );
    }
    _textTextureHash[GameOverMenuItem::TITLE].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE2)], "GAME OVER", whiteTextColor);
    _textTextureHash[GameOverMenuItem::PLAY_AGAIN].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Again", whiteTextColor);
    _textTextureHash[GameOverMenuItem::QUIT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", whiteTextColor);
    _textTextureHash[GameOverMenuItem::PLAY_AGAIN_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Again", selectTextColor);
    _textTextureHash[GameOverMenuItem::QUIT_SELECT].loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", selectTextColor);

    
    Point titlePos{ static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[GameOverMenuItem::TITLE].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[GameOverMenuItem::TITLE].getHeight())/3)};
    _textObjectHash[GameOverMenuItem::TITLE] = GameObject::Create(ObjectType::STATIC, titlePos, &_textTextureHash[GameOverMenuItem::TITLE]); 
    
    Point playPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[GameOverMenuItem::PLAY_AGAIN].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[GameOverMenuItem::PLAY_AGAIN].getHeight())/2)};
    _textObjectHash[GameOverMenuItem::PLAY_AGAIN] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[GameOverMenuItem::PLAY_AGAIN]); 
    _textObjectHash[GameOverMenuItem::PLAY_AGAIN_SELECT] = GameObject::Create(ObjectType::STATIC, playPos, &_textTextureHash[GameOverMenuItem::PLAY_AGAIN_SELECT]); 


    Point quitPos{  static_cast<double>((AsteroidConstants::SCREEN_WIDTH - _textTextureHash[GameOverMenuItem::QUIT].getWidth())/2),
                    static_cast<double>((AsteroidConstants::SCREEN_HEIGHT - _textTextureHash[GameOverMenuItem::QUIT].getHeight())/1.8)};
    _textObjectHash[GameOverMenuItem::QUIT] = GameObject::Create(ObjectType::STATIC, quitPos, &_textTextureHash[GameOverMenuItem::QUIT]); 
    _textObjectHash[GameOverMenuItem::QUIT_SELECT] = GameObject::Create(ObjectType::STATIC, quitPos, &_textTextureHash[GameOverMenuItem::QUIT_SELECT]); 

}

GameState MenuGameOver::run()
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

        
void MenuGameOver::renderItems()
{
    SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderClear(_prenderer);

    SDL_Rect backgroundRect{0,0,AsteroidConstants::SCREEN_WIDTH, AsteroidConstants::SCREEN_HEIGHT};
    static_cast<StaticObject*>(_backgroundObject)->render(_prenderer, &backgroundRect);

    _textObjectHash[GameOverMenuItem::TITLE]->render(_prenderer);
    if(_state){
        _textObjectHash[GameOverMenuItem::PLAY_AGAIN_SELECT]->render(_prenderer);
        _textObjectHash[GameOverMenuItem::QUIT]->render(_prenderer);
    }
    else{
        _textObjectHash[GameOverMenuItem::PLAY_AGAIN]->render(_prenderer);
        _textObjectHash[GameOverMenuItem::QUIT_SELECT]->render(_prenderer);
    }
    
    SDL_RenderPresent(_prenderer);

}

void MenuGameOver::toggleState()
{
    _state = !_state;
}

GameState MenuGameOver::select()
{
    if(_state){
        return GameState::PLAY_AGAIN;
    }
    else{
        return GameState::QUIT;
    }
}
