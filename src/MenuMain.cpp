#include "MenuMain.h"

MenuMain::MenuMain()
{}

MenuMain::~MenuMain()
{}

void MenuMain::init(SDL_Renderer* renderer, std::vector<TTF_Font*> &mainFonts)
{
    SDL_Color textColor{255,255,255};

    _prenderer = renderer;

    _textTitle.loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::TITLE1)], "Asteroids", textColor);
    _textPlay.loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Play Game", textColor);
    _textQuit.loadFromRenderedText(_prenderer, mainFonts[static_cast<int>(FontType::MENU)], "Quit", textColor);
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
        }

        SDL_SetRenderDrawColor(_prenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear(_prenderer);

        SDL_RenderPresent(_prenderer);

    }
}