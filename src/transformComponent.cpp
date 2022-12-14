#include "../headers/TransformComponent.h"

TransformComponent::TransformComponent(int x, int y) : pos(x,y){}

TransformComponent::TransformComponent(int x, int y, int speed, int width, int height)
        : pos(x,y), speed(speed), width(width), height(height){}

TransformComponent::TransformComponent(int x, int y, int width, int height) : pos(x,y), width(width), height(height) {
}
void TransformComponent::init(){
    velocity.Zero();
}

void TransformComponent::update(){
    if(delay) {
        if(SDL_GetTicks() - lastFrame < delayMillsec)
            return;
        velocity.setY(1);
        delay = false;
    }
    if(dead) return;
    Vector2D curPos = pos;
    curPos.setX(curPos.getX() + speed * velocity.getX());
    curPos.setY(curPos.getY() + speed * velocity.getY());
    setPos(curPos);


}

int TransformComponent::getSpeed() const {
    return speed;
}

int TransformComponent::getWidth() const {
    return width;
}

int TransformComponent::getHeight() const {
    return height;
}

Vector2D TransformComponent::getPos() const {
    return pos;
}


void TransformComponent::setSpeed(int m_speed) {
    if(m_speed >=0) speed = m_speed;
}

void TransformComponent::setWidth(int m_width) {
    if(m_width >=0 && m_width<=Parameters::SCREEN_W) width = m_width;
}

void TransformComponent::setHeight(int m_height) {
    if(m_height >=0 && m_height<=Parameters::SCREEN_W) height = m_height;
}

void TransformComponent::setPos(const Vector2D &m_pos) {
   if (m_pos.getX() >= 0 && m_pos.getX() <= Parameters::SCREEN_W - Parameters::PIXELS
   && m_pos.getY() >= Parameters::PIXELS && m_pos.getY() <= Parameters::SCREEN_H - Parameters::PIXELS)
        pos = m_pos;
}

bool TransformComponent::isDelayed() const {
    return delay;
}

void TransformComponent::setDelay(uint32_t millSecs) {
    this->delayMillsec = millSecs;
    this->delay = true;
    lastFrame = SDL_GetTicks();
}

void TransformComponent::setDeath(bool isDead) {
    this->dead = isDead;
}

bool TransformComponent::isDead() const {
    return dead;
}

TransformComponent::TransformComponent(const TransformComponent &other) {
    dead = other.dead;
    pos = other.pos;
    delay = other.delay;
    lastFrame = other.lastFrame;
    delayMillsec = other.delayMillsec;
    speed = other.speed;
    width = other.width;
    height = other.height;
}
