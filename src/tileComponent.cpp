#include "../headers/TileComponent.h"

TileComponent::TileComponent(int x, int y, int w, int h, MapTilesID id, unsigned int points, groupLabels gr){
    tileRect.x = x;
    tileRect.y = y;
    tileRect.w = w;
    tileRect.h = h;
    group = gr;
    tilePoints = points;
    tileID = id;
    switch(tileID){
        case MapTilesID::dirtID:
            path = "img/dirt.png";
            break;
        case MapTilesID::diamondID:
            path = "img/diamond.png";
            break;
        case MapTilesID::moneyBagID:
            path = "img/MoneyBag.png";
            break;
    }
}

void TileComponent::init(){
    entity->addComponent<TransformComponent>(tileRect.x,tileRect.y,tileRect.w,tileRect.h);
    transform = &entity->getComponent<TransformComponent>();
    entity->addComponent<SpriteComponent>(path.c_str(),tilePoints);
    sprite = &entity->getComponent<SpriteComponent>();
    entity->addGroup(group);
    switch (tileID) {
        case MapTilesID::dirtID:
            entity->addComponent<CollisionComponent>("dirt",tileRect.x,tileRect.y,tileRect.w,tileRect.h);
            break;
        case MapTilesID::diamondID:
            entity->addComponent<CollisionComponent>("diamond",tileRect.x,tileRect.y,24,24);
            break;
        case MapTilesID::moneyBagID:
            entity->addComponent<CollisionComponent>("moneybag",tileRect.x,tileRect.y,tileRect.w,tileRect.h);
    }

}

MapTilesID TileComponent::getTileID() const {
    return tileID;
}

unsigned int TileComponent::getTilePoints() const {
    return tilePoints;
}

groupLabels TileComponent::getGroup() const {
    return group;
}
