#pragma once

#include <string>
#include "Components.h"
#include "Game.h"

/**
 * A class to crate the collision block around an object.
 */

class CollisionComponent : public Component{
private:
    SDL_Rect collider; /**< Rectangle for the collision */
    TransformComponent* transform; /**< TransformComponent in order to know how to move the collider */
    std::string tag; /**< A tag to tell the difference between each collider */
public:
    CollisionComponent(std::string&& tag, int x, int y, int width, int height);
    /**
     * Initialise the TransformComponent and add the address of the collider to the Game::colliders
     */
    void init() override;
    /**
     * Move the collider based on the TransformComponent
     */
    void update() override;
    /**
     * A simple getter
     * @return The object's tag
     */
    std::string getTag() const;
    /**
     * A simple getter
     * @return The object's collider
     */
    SDL_Rect getCollider() const;
    /**
     * Set the object's tag
     * @param TAG The new tag
     */
    void setTag(const std::string& TAG);
    /**
     * Set the object's collider
     * @param m_collider The new SDL_Rect for the collider
     */
    void setTransform(TransformComponent* _transform);
};