#pragma once
#include "Game.h"
#include "Components.h"

/**
 * This class finds the shortest path for the monsters to chase the player.
 */

class ChaseComponent : public Component{
private:
    Entity* target; /**< The target for the monsters to chase */
    int dist[Parameters::WIDTH][Parameters::HEIGHT]; /**< The array used for the bfs algorithm for shortest path */
    bool visited[Parameters::WIDTH][Parameters::HEIGHT]; /**< Check if dist's cell has been visited */

    void clearDist(); /**< Set all the dist cells to -1 */
    void move(); /** Move the object to a cell closer to the target */
public:
    explicit ChaseComponent(Entity* target);
    /**
     * Set the object's target to chase.
     * @param target The target which will be chased.
     */
    void setTarget(Entity* target);
    /**
     * Find the shortestPath using the BFS algorithm to the target based on a given position.
     * @param pos The position where the target is.
     */
    void shortestPath(Vector2D pos);
    /**
     * The update function which will be called to update dist and move the object using move() function
     */
    void update() override;
    void init() override{};
};