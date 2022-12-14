#pragma once

#include "../SDL2/SDL.h"
#include "CollisionComponent.h"
/**
 * A simple class which will detect the simplest AABB collision
 */
class Collision{
public:
    /**
     * Check if there is a collision between two rectangles.
     * @param recA The first rectangle.
     * @param recB The second rectangle.
     * @return True if there is a collision. False otherwise.
     */
    static bool hasCollision(const SDL_Rect& recA, const SDL_Rect& recB);
    /**
     * Check if there is a collision between two CollisionComponents.
     * @param colA The first CollisionComponent.
     * @param colB The second CollisionComponent.
     * @return True if there is a collision. False otherwise
     */
    static bool hasCollision(const CollisionComponent& colA, const CollisionComponent& colB);
};