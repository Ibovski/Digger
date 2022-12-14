#pragma once
#include "Game.h"

/**
 * A simple class which will only draw and load SDL_Textures.
 */
class TextureManager{
public:
    /**
     * A static function to load the SDL_Texture
     * @param filename The path to the image we want to load.
     * @return SDL_Texture* if the file is loaded correctly.
     */
    static SDL_Texture* LoadTexture(const char* filename);
    /**
     * A static function to draw a SDL_Texture to the screen.
     * @param text SDL_Texture we want to draw.
     * @param src  SDL_Rect the source of the image we want to draw.
     * @param dest SDL_Rect the destination of the image we want to draw.
     * @param angle The angle we want to rotate the image.
     * @param center The center of the image.
     * @param flag SDL_RenderFlip value
     */
    static void drawTexture(SDL_Texture *text, SDL_Rect* src, SDL_Rect* dest,
                            double angle, SDL_Point* center, SDL_RendererFlip flag);


};