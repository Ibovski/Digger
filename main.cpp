#include "headers/Game.h"

const int frameDelay = 1000 / Parameters::FRAMES;

int main( int argc, char* args[]) {
    uint32_t frameStart;
    int frameTime;
    Game* game = &Game::getInstance();
    game->Init("Digger",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,Parameters::SCREEN_W,Parameters::SCREEN_H,false);

    while(game->running()){
        frameStart = SDL_GetTicks();

        game->eventHandle();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}
