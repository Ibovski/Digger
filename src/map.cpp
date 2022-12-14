#include "../headers/Map.h"
#include <fstream>

void Map::loadMap(const std::string& path, int sizeX, int sizeY) {
    char tile;
    std::fstream mapFile(path);
    if(!mapFile.is_open()) throw std::runtime_error("Could not open the file");
    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            mapFile.get(tile);
            MapTilesID tileID = static_cast<MapTilesID>(tile-'0');

            Game::getInstance().map[i][j] = static_cast<int>(tileID);
            if(tileID == MapTilesID::dirtID) Game::getInstance().AddTile(j*Parameters::PIXELS,(i)*Parameters::PIXELS, MapTilesID::dirtID,TilePoints::dirtPoints,groupMap);
            if(tileID == MapTilesID::diamondID) Game::getInstance().AddTile(j*Parameters::PIXELS, i*Parameters::PIXELS, MapTilesID::diamondID,TilePoints::diamondPoints,groupRewards);
            if(tileID == MapTilesID::moneyBagID) Game::getInstance().AddTile(j*Parameters::PIXELS,i*Parameters::PIXELS,MapTilesID::moneyBagID,TilePoints::moneyBagPoints,groupRewards);
            if(tileID == MapTilesID::dirtAndDiamondID) {
                Game::getInstance().AddTile(j*Parameters::PIXELS,(i)*Parameters::PIXELS, MapTilesID::dirtID,TilePoints::dirtPoints,groupMap);
                Game::getInstance().AddTile(j*Parameters::PIXELS,i*Parameters::PIXELS,MapTilesID::diamondID,TilePoints::diamondPoints,groupRewards);
            }
            if(tileID == MapTilesID::dirtAndMoneyBagID){
                Game::getInstance().AddTile(j*Parameters::PIXELS,(i)*Parameters::PIXELS, MapTilesID::dirtID,TilePoints::dirtPoints,groupMap);
                Game::getInstance().AddTile(j*Parameters::PIXELS,i*Parameters::PIXELS,MapTilesID::moneyBagID,TilePoints::moneyBagPoints,groupRewards);
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::Init() {
    for(int i = 0; i < Parameters::SCOREBOARD - Parameters::LIVES; i++){
        scoreBoardIMGpath[i] = "img/number0.png";
    }
    for(int i = Parameters::SCOREBOARD - Parameters::LIVES; i < Parameters::SCOREBOARD; i++){
        scoreBoardIMGpath[i] = "img/player1.png";
    }
    for(int i = 0; i < Parameters::SCOREBOARD; i++){
        scoreBoardEntities[i] = Game::getInstance().manager.addEntity();
        scoreBoardEntities[i]->addComponent<TransformComponent>((i + 1) * Parameters::PIXELS, 0, Parameters::PIXELS, Parameters::PIXELS);
        scoreBoardEntities[i]->addComponent<SpriteComponent>(scoreBoardIMGpath[i].c_str());
        scoreBoardEntities[i]->addGroup(groupMap);
    }
}

void Map::UpdateScoreBoard(unsigned int score, unsigned int lives) {
    for(int i = Parameters::SCOREBOARD - 1; i >= Parameters::SCOREBOARD - (Parameters::LIVES - lives); i--){
        scoreBoardIMGpath[i] = "";
    }
    for(int i = Parameters::SCOREBOARD - Parameters::LIVES - 1; i >= 0; i--){
        if(score == 0) break;
        unsigned int x = score % 10;
        score/=10;
        scoreBoardIMGpath[i] = "img/number";
        scoreBoardIMGpath[i] += char(x + '0');
        scoreBoardIMGpath[i] += ".png";

    }
    for(int i = 0; i < Parameters::SCOREBOARD; i++){
        scoreBoardEntities[i]->getComponent<SpriteComponent>().setTex(scoreBoardIMGpath[i].c_str());
    }
}

Map &Map::getInstance() {
    static Map instance;
    return instance;
}



