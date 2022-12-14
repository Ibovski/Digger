#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../SDL2/SDL.h"
#include "CollisionComponent.h"

class SpriteComponent;

/**
 * Class to create all the tiles in the Game::map array.
 *
 * Each tile has TransformComponent and SpriteComponent
 */
class TileComponent : public Component{
private:
    TransformComponent *transform;
    SpriteComponent* sprite;
    SDL_Rect tileRect; /**< SDL_Rect the dimensions of the tile */
    MapTilesID tileID; /**< The ID type of the tile */
    unsigned int tilePoints; /**< The points the tile gives */
    std::string path; /** The path to the image of the tile */
    groupLabels group; /** The group the tile belongs to */
public:

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, MapTilesID id,unsigned int points,groupLabels gr);
    /**
     * Initialise the transform and sprite component.
     */
    void init() override;
    /**
     * Does nothing
     */
    void update() override{};
    /**
     * Return the Tile type ID.
     * @return Return the Tile type ID.
     */
    MapTilesID getTileID() const;
    /**
     * Return the Tile points.
     * @return Return the Tile points.
     */
    unsigned int getTilePoints() const;
    /**
     * Return the Tile's group.
     * @return Return the Tile's group.
     */
    groupLabels getGroup() const;
};