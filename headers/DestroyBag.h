#pragma once

#include "Components.h"

class CollisionComponent;

/**
 * The class that implements the moneyBag transformation.
 */

class DestroyBag : public Component{
private:
    int lastPosX; /**< The index in the Game::map array of the last xPosition where the moneyBag was. */
    int lastPosY; /**< The index in the Game::map array of the last yPosition where the moneyBag was. */
    std::string destroyedBagIMG; /**< The path for the image after the bag is destroyed */
    bool destroyed = false; /**< Tells if the bag is destroyed */
    SpriteComponent* sprite; /**< The SpriteComponent where the img will be changed. */
    CollisionComponent* collision; /**< We need that so we can change the Tag when the bag is destroyed */
    void change(); /**< This function changes the img, tag and points of the destroyedBag */
public:
    DestroyBag(std::string  img, int _lastPoX, int _lastPosY);
    /**
     * Takes the Sprite and Collision Component from its entity parent
     */
    void init() override;
    /**
     * Checks if the bag is destroyed every frame. If so calls the change() function
     */
    void update() override;
    /**
     * Set the yPosition of the moneyBag
     * @param Y The new yPosition.
     */
    void setLastPosY(int Y);
    /**
     * Set the xPosition of the moneyBag
     * @param X The new xPosition.
     */
    void setLastPosX(int X);
    /**
     * Makes the destroyed parameter to true.
     */
    void destroy() {destroyed = true;}
    /**
     * Getter for the last yPosition the moneybag was..
     * @return lastPosY
     */
    int getLastPosY() const {return lastPosY;}
    /**
     * Getter for the last xPosition the moneybag was..
     * @return lastPosX
     */
    int getLastPosX() const {return lastPosX;}
    /**
     * Checks if the moneyBag is destroyed.
     * @return destroyed.
     */
    bool isDestroyed() const {return destroyed;}
};