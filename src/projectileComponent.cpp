#include "../headers/ProjectileComponent.h"

void ProjectileComponent::init() {
        clear();
        transform = new TransformComponent(entity->getComponent<TransformComponent>());
        transform->setWidth(Parameters::PIXELS / 2);
        transform->setHeight(Parameters::PIXELS / 2 );
        transform->setSpeed(3);
        sprite = new SpriteComponent("img/projectile.png");
        sprite->setTransform(transform);
        sprite->setSrc(0, 0, transform->getWidth(), transform->getHeight());
        sprite->setDest(transform->getPos().getX(), transform->getPos().getY(), transform->getWidth(),
                        transform->getHeight());

        collision = new CollisionComponent("projectile",0,0,transform->getWidth(),transform->getHeight());
        collision->setTransform(transform);
}

ProjectileComponent::~ProjectileComponent() {
    clear();
}

void ProjectileComponent::update() {
    if(active) {
        transform->update();
        sprite->setDest(transform->getPos().getX() + Parameters::PIXELS / 4, transform->getPos().getY() + Parameters::PIXELS / 4, transform->getWidth(),
                        transform->getHeight());
        collision->update();
        Vector2D currPos = transform->getPos();
        currPos += transform->velocity * transform->getSpeed();
        if(currPos.getX() < 0 || currPos.getX() > Parameters::SCREEN_W  - Parameters::PIXELS
        || currPos.getY() < Parameters::PIXELS || currPos.getY() > Parameters::SCREEN_H - Parameters::PIXELS)
             active = false;
    }
}

void ProjectileComponent::clear() {
    delete transform;
    delete sprite;
    delete collision;
    transform = nullptr;
    sprite = nullptr;
    collision = nullptr;
}

void ProjectileComponent::draw() {
    if(active) sprite->draw();
}

void ProjectileComponent::activate() {

    if(shootingDelay == 0 || SDL_GetTicks() - shootingDelay >= Parameters::SHOOTINGDELAY) {

        if (!active) {
            shootingDelay = SDL_GetTicks();
            init();
        }
        active = true;
    }
}

bool ProjectileComponent::isActive() const {
    return active;
}

void ProjectileComponent::destroy() {
    active = false;
}

CollisionComponent *ProjectileComponent::getCollisionComponent() const {
    return collision;
}
