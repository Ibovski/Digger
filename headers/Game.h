#pragma once
#include <vector>
#include <iostream>
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "ENUMparameters.h"
#include "../headers/Components.h"

class CollisionComponent;
class Manager;
class Map;
class Entity;


/**
 * The main Game class. It is a singleton class.
 * Here are the all the game objects and the main update / render functions
 */

class Game{
private:

    bool isRunning = false; /**< Check if the game is running. */
    int lives = Parameters::LIVES; /**< Player's lives remaining */
    unsigned int enemiesLeft = Parameters::enemyCount; /**< The number of enemies */
    uint32_t delaySpawn = 0;
    Game() = default;
    void createPlayer(); /**< Creates a player if there is none */
    void createEnemy(); /**< Creates the monster which will chase the player */
    void end(); /**< Ends the game */
    void restartGame();
    void clearMonsters(bool destroyAll);

public:
    std::vector<Entity* > movingEntities; /**< The vector containing all the moving entities */
    Entity* player; /**< The player object */
    std::vector<Entity*> monsters;/** A std::vector of monster objects */
    SDL_Window* window; /** Main game window */
    SDL_Renderer* renderer; /** Main renderer */
    SDL_Event event; /** Event member */
    std::vector<CollisionComponent*> colliders; /**< The vector containing all the collisions */
    Manager manager; /**< The manager which contains all the entities in the game */
    unsigned int score; /** The score of the player */
    int map[Parameters::WIDTH][Parameters::HEIGHT]; /** An array of the map tiles */
    /**
     * This creates a static Game instance
     * @return instance of type Game
     */
    static Game& getInstance();

    ~Game() = default;
    Game(const Game&) = delete;
    Game operator=(const Game&) = delete;

    /**
     *  This functions is used to crete the initial window and renderer
     * @param title -> The name of the game window
     * @param xpos -> xPosition of the game window
     * @param ypos -> yPosition of the game window
     * @param width -> game window's width
     * @param height-> game window's height
     * @param fullscreen -> True if fullscreen ; False if not
     * @return none
     */
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    /**
     * Function to check if the game window is closed
     */
    void eventHandle();
    /**
     * Update the game every frame.
     * Update all the player / monsters movement and collision detecting.
     *
     * Checks if the player and the enemies are alive. If not create them.
     */
    void update();
    /**
     * Render all the game objects to the main screen window.
     */
    void render();
    /**
     * Destroys the main SDL_Window and SDL_Renderer
     */
    void clean();
    /**
     * Check if the game is closed
     * @return isRunning -> bool
     */
    bool running() const {return isRunning;}

    /**
     * A function which creates all the tiles which are not player nor enemies.
     * @param xpos xPosition of the tile which will be created.
     * @param ypos yPosition of the tile which will be created.
     * @param ID  Tile's ID.
     * @param points The points which will be added to the @param score.
     * @param group Add the tile to the group it belongs. This helps rendering the map properly.
     */
    void AddTile(int xpos, int ypos, MapTilesID ID,unsigned int points,groupLabels group);


};
