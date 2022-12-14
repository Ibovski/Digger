#include "../headers/SpriteComponent.h"

SpriteComponent::SpriteComponent(const char *path) {
    setTex(path);
}

SpriteComponent::SpriteComponent(const char *path, unsigned int points) : points(points) {
    setTex(path);
}
void SpriteComponent::init() {
    transform = &entity->getComponent<TransformComponent>();
    setSrc(0,0,transform->getWidth(),transform->getHeight());
    setDest(0,0,transform->getWidth(),transform->getHeight());

}

void SpriteComponent::update() {
    dest.x = transform->getPos().getX();
    dest.y = transform->getPos().getY();
}

SpriteComponent::~SpriteComponent() {
    SDL_DestroyTexture(texture);
}

void SpriteComponent::setTex(const char *path){
    texture = TextureManager::LoadTexture(path);
}

void SpriteComponent::draw(){
    TextureManager::drawTexture(texture,&src,&dest,angle, nullptr,flag);
}

SDL_RendererFlip SpriteComponent::getFlag() const {
    return flag;
}


void SpriteComponent::setFlag(const SDL_RendererFlip &m_flag) {
    flag = m_flag;
}

void SpriteComponent::setAngle(double m_angle) {
    angle = m_angle;
}

unsigned int SpriteComponent::getPoints() const {
    return points;
}

void SpriteComponent::setPoints(unsigned int P) {
    points = P;
}

void SpriteComponent::setTransform(TransformComponent *_transform) {
    this->transform = _transform;
}

void SpriteComponent::setSrc(int x, int y, int w, int h) {
    src.x = x;
    src.y = y;
    src.w = w;
    src.h = h;
}

void SpriteComponent::setDest(int x, int y, int w, int h) {
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}

