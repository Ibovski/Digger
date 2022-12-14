#pragma once

#include "Components.h"
#include "Vector2D.h"

enum FACING{
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4
};

/**
 * Class which will take keyboard inputs.
 */
class Keyboard : public Component{
private:
    bool keyPressed = false; /**< Tells if a key is pressed */
    Vector2D oldVel;
    TransformComponent* transform; /**< The position and velocity of the object we will control */
    FACING towards = RIGHT;
public:
    /**
     * A initialise function in order to init the TransformComponent.
     */
    void init() override;
    /**
     * The function which will update velocity based on pressed key.
     */
    void update() override;


};