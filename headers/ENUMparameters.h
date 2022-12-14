#pragma once

/**
 * namespace for the main parameters in the game
 */
namespace Parameters {
    static constexpr int PIXELS = 32;
    static constexpr int WIDTH = 11;
    static constexpr int HEIGHT = 16;
    static constexpr int SCREEN_W = 512;
    static constexpr int SCREEN_H = 352;
    static constexpr int SCOREBOARD = 8;
    static constexpr int LIVES = 3;
    static constexpr int FRAMES = 60;
    static constexpr int enemyCount = 3;
    static constexpr int SPAWNDELAY = 4000;
    static constexpr int MONEYBAGFALL = 1000;
    static constexpr int SHOOTINGDELAY = 4000;
};

/**
 * enum for the different groups the entities will be add to.
 */
enum groupLabels{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupRewards
};
/**
 * enum for the tiles ID.
 */
enum class MapTilesID{
    dirtID = 4,
    diamondID = 1,
    moneyBagID = 2,
    dirtAndDiamondID = 5,
    dirtAndMoneyBagID = 6
};
/**
 * namespace for the tiles Points.
 */
namespace TilePoints{
    static constexpr int dirtPoints = 0;
    static constexpr int diamondPoints = 25;
    static constexpr int moneyBagPoints = 0;
    static constexpr int destroyedBagPoints = 250;
    static constexpr int enemyPoints = 500;
};