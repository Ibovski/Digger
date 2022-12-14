#include "../headers/TextureManager.h"
SDL_Texture *TextureManager::LoadTexture(const char *filename) {

    SDL_Surface* tempsurface = IMG_Load(filename);
    SDL_Texture* res = SDL_CreateTextureFromSurface(Game::getInstance().renderer,tempsurface);
    SDL_FreeSurface(tempsurface);
    return res;
}
void TextureManager::drawTexture(SDL_Texture *text, SDL_Rect* src, SDL_Rect* dest,
                                 double angle, SDL_Point* center, SDL_RendererFlip flag) {
   // std::cout<<dest->x<<" "<<dest->y<<"\n";
    SDL_RenderCopyEx(Game::getInstance().renderer,text,src,dest, angle, center,flag);
}
