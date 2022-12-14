#include "../headers/DestroyBag.h"


DestroyBag::DestroyBag(std::string img, int _lastPosX, int _lastPosY) :
    destroyedBagIMG(std::move(img)),lastPosX(_lastPosX), lastPosY(_lastPosY){}

void DestroyBag::init() {
    sprite = &this->entity->getComponent<SpriteComponent>();
    collision = &this->entity->getComponent<CollisionComponent>();
}

void DestroyBag::change() {
    sprite->setTex(destroyedBagIMG.c_str());
    sprite->setPoints(TilePoints::destroyedBagPoints);
    collision->setTag("destroyedBag");
    this->entity->getComponent<TransformComponent>().setDeath(true);
}

void DestroyBag::update() {
    if(destroyed) change();
}

void DestroyBag::setLastPosY(int Y) {
    lastPosY = Y;
}

void DestroyBag::setLastPosX(int X) {
    lastPosX = X;
}

