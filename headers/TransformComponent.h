#pragma once

#include "Components.h"
#include "Vector2D.h"
#include "ENUMparameters.h"

/**
 * This class manages all the position changing.
 */
class TransformComponent : public Component{
private:
    bool dead = false; /**< If the object is dead it should not move */
    Vector2D pos; /**< The position of the object */
    bool delay = false; /**< This is specifically for the moneyBag. Set it true to implement the falling mechanic */
    uint32_t lastFrame; /**< This is specifically for the moneyBag. Remember the frame when delay was set to true */
    uint32_t delayMillsec = 2 * 1000; /**< The delay time before the action to happen */
    int speed = 4; /**< The speed of the object */
    int width = Parameters::PIXELS; /**< The width of the object */
    int height = Parameters::PIXELS; /**< The height of the object */
public:
    Vector2D velocity; /** The velocity of the object */
    TransformComponent() = default;
    TransformComponent(const TransformComponent& other);
    TransformComponent(int x, int y);
    TransformComponent(int x, int y, int speed, int width, int height);
    TransformComponent(int x, int y, int width, int height);

    /**
     * Set the velocity to zero;
     */
    void init() override;
    /**
     * Update the position of the object.
     */
    void update() override;
    /**
     * Return the speed of the object.
     * @return Return the speed of the object.
     */
    int getSpeed() const;
    /**
     * Return the width of the object.
     * @return Return the width of the object.
     */
    int getWidth() const;
    /**
     * Return the height of the object.
     * @return Return the height of the object.
     */
    int getHeight() const;
    /**
     * Return the position of the object.
     * @return Return the position of the object.
     */
    Vector2D getPos() const;
    /**
     * Check if the update should be delayed.
     * @return True if delayed. False otherwise.
     */
    bool isDelayed() const;
    /**
     * Check if the object is dead.
     * @return True if is dead. False otherwise.
     */
    bool isDead() const;
    /**
     * Change the death parameter.
     * @param isDead True -> dead. False -> alive.
     */
    void setDeath(bool isDead);
    /**
     * Set the delay to true and how long the update should be delayed.
     * @param millSecs The time the update should wait.
     */
    void setDelay(uint32_t millSecs = 2*1000);
    /**
     * Set the speed of the object.
     * @param m_speed The speed for the object.
     */
    void setSpeed(int m_speed);
    /**
     * Set the width of the object.
     * @param m_width The width for the object.
     */
    void setWidth(int m_width);
    /**
     * Set the height of the object.
     * @param m_height The height for the object.
     */
    void setHeight(int m_height);
    /**
     * Set the position of the object.
     * @param m_pos The position for the object.
     */
    void setPos(const Vector2D& m_pos);
};