#pragma once

#include "Components.h"
/**
 * The projectile class
 */
class ProjectileComponent : public Component{
private:
    bool active = false; /**< Tells if there is a bullet */
    SpriteComponent* sprite = nullptr; /**< The SpriteComponent of the bullet */
    CollisionComponent* collision = nullptr; /**< The CollisionComponent of the bullet */
    uint32_t shootingDelay = 0; /**< The delay between each bullet */
public:
    TransformComponent* transform = nullptr; /**< The TransformComponent of the bullet */
    ProjectileComponent() = default;
    ~ProjectileComponent() override;
    void init() override; /**< Initialise all the components of the projectile */
    void update() override; /**< Update all the components of the projectile */
    void draw() override; /**< Draw the bullet */
    void clear(); /** Free components' memory */
    void activate(); /** Display the projectile on the screen */
    void destroy(); /** Destroy the projectile */
    /**
    * Check if there is a projectile on the screen
    * @return True if there is. False otherwise
    */
    bool isActive() const;
    /**
     * Get the CollisionComponent of the projectile
     * @return CollisionComponent
     */
    CollisionComponent* getCollisionComponent() const;

};