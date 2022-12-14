#pragma once

#include "Components.h"
#include "TextureManager.h"

class TransformComponent;
/**
 * SpriteComponent class is used to set SDL_texture , rotate textures and draw them on the window screen.
 */
class SpriteComponent : public Component{
private:
    TransformComponent* transform; /**< The TransformComponent we need in order to draw the image*/
    SDL_Texture* texture; /**< This will hold our texture */
    SDL_Rect src,dest;
    SDL_RendererFlip flag = SDL_FLIP_NONE;
    double angle = 0;
    unsigned int points = 0; /**< the points this sprite will give to the player*/
public:
    SpriteComponent() = default;
    SpriteComponent(const char* path);
    SpriteComponent(const char* path, unsigned int points);
    ~SpriteComponent() override;
    /**
     * Initialise the TransformComponent.
     */
    void init() override;
    /**
     * Update the img position.
     */
    void update() override;
    /**
     * Draw the img.
     */
    void draw() override;
    /**
     * Return the SDL_RenderFlip
     * @return flag
     */
    SDL_RendererFlip getFlag() const;
    /**
     * Return the points for this sprite.
     * @return points;
     */
    unsigned int getPoints() const;
    /**
     * Set the sprite points.
     * @param _points The points to be set.
     */
    void setPoints(unsigned int _points);
    /**
     * Set the texture img.
     * @param path The path of the image.
     */
    void setTex(const char* path);
    /**
     * Set the SDL_RenderFlip flag.
     * @param flag SDL_RenderFlip value
     */
    void setFlag(const SDL_RendererFlip& flag);
    /**
     * Set the rotation angle for the image.
     * @param angle double type angle.
     */
    void setAngle(double angle);

    void setTransform(TransformComponent* transform);
    void setSrc(int x, int y, int w, int h);
    void setDest(int x, int y, int w, int h);

};