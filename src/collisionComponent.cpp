#include "../headers/CollisionComponent.h"

CollisionComponent::CollisionComponent(std::string &&tag, int x, int y, int width, int height): tag(std::move(tag)){
    collider.x = x;
    collider.y = y;
    collider.w = width;
    collider.h = height;
}

void CollisionComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    Game::getInstance().colliders.emplace_back(this);
}

void CollisionComponent::update() {
    collider.x = transform->getPos().getX();
    collider.y = transform->getPos().getY();
}

SDL_Rect CollisionComponent::getCollider() const {
    return collider;
}

std::string CollisionComponent::getTag() const{
    return tag;
}

void CollisionComponent::setTag(const std::string& TAG) {
    this->tag = TAG;
}

void CollisionComponent::setTransform(TransformComponent *_transform) {
    transform = _transform;
}
