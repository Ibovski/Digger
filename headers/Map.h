#pragma once
#include "Game.h"
#include "Components.h"

/**
 * A singleton class for the game's map
 */
class Map{
private:
    std::string scoreBoardIMGpath[Parameters::SCOREBOARD]; /**< The path for the images for the scoreBoardIMGpath */
    Entity* scoreBoardEntities[Parameters::SCOREBOARD]; /**<An array of the all scoreboard objects */
    Map() = default;
public:
    /**
     * Initialise the scoreBoardIMGpath and the scoreBoardEntities.
     */
    void Init();
    /**
     * Update the score and the player's lives.
     * @param score The score of the game in the current state.
     * @param lives The remaining lives the player has.
     */
    void UpdateScoreBoard(unsigned int score, unsigned int lives);
    /**
     * A static function to read a file and create all the tiles.
     * @param path The path for the file.
     * @param sizeX The width of the file.
     * @param sizeY The height of the file.
     */
    static void loadMap(const std::string& path, int sizeX, int sizeY);
    /**
     * A static function to get an instance of Map or create a new one if there is none.
     * @return Map&
     */
    static Map& getInstance();
    Map(const Map& other) = delete;
    Map& operator=(const Map& other) = delete;
};