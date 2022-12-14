#include "../headers/Keyboard.h"
void Keyboard::init() {
    transform = &entity->getComponent<TransformComponent>();

}

void Keyboard::update() {
    SpriteComponent* curr =&entity->getComponent<SpriteComponent>();
    bool keepMoving = false;
    if(transform->getPos().getX()  % Parameters::PIXELS != 0 || transform->getPos().getY() % Parameters::PIXELS != 0){
        keepMoving = true;
    }
    else Game::getInstance().map[transform->getPos().getY() / Parameters::PIXELS][transform->getPos().getX() / Parameters::PIXELS] = 0;
    if(Game::getInstance().event.type == SDL_KEYDOWN && Game::getInstance().event.key.keysym.sym == SDLK_SPACE){
        if(!entity->getComponent<ProjectileComponent>().isActive()) {
            entity->getComponent<ProjectileComponent>().activate();
            Vector2D projectVel;
            switch (towards) {
                case UP:
                    projectVel.setY(-1);
                    break;
                case DOWN:
                    projectVel.setY(1);
                    break;
                case LEFT:
                    projectVel.setX(-1);
                    break;
                case RIGHT:
                    projectVel.setX(1);
                    break;
            }
            entity->getComponent<ProjectileComponent>().transform->velocity = projectVel;
        }
    }
    if(Game::getInstance().event.type == SDL_KEYDOWN && !keyPressed && !transform->isDead()){
        transform->velocity.Zero();
        switch(Game::getInstance().event.key.keysym.sym){
            case SDLK_UP:
                if(keepMoving && oldVel.getY() == 0){
                    transform->velocity = oldVel;
                    break;
                }
                transform->velocity.setY(-1);
                towards = UP;
                keyPressed = true;
                if(curr->getFlag() == SDL_FLIP_HORIZONTAL) curr->setAngle(90);
                else curr->setAngle(-90);
                break;
            case SDLK_DOWN:
                if(keepMoving && oldVel.getY() == 0){
                    transform->velocity = oldVel;
                    break;
                }
                transform->velocity.setY(1);
                towards = DOWN;
                keyPressed = true;
                if(curr->getFlag() == SDL_FLIP_HORIZONTAL) curr->setAngle(-90);
                else curr->setAngle(90);
                break;
            case SDLK_RIGHT:
                if(keepMoving && oldVel.getX() == 0){
                    transform->velocity = oldVel;
                    break;
                }
                transform->velocity.setX(1);
                towards = RIGHT;
                keyPressed = true;
                curr->setFlag(SDL_FLIP_NONE);
                curr->setAngle(0);
                break;
            case SDLK_LEFT:
                if(keepMoving && oldVel.getX() == 0){
                    transform->velocity = oldVel;
                    break;
                }
                transform->velocity.setX(-1);
                towards = LEFT;
                keyPressed = true;
                curr->setFlag(SDL_FLIP_HORIZONTAL);
                curr->setAngle(0);
                break;
        }
    }

    if(Game::getInstance().event.type == SDL_KEYUP){

        switch(Game::getInstance().event.key.keysym.sym){
            case SDLK_SPACE:
                break;
            default:
                if(keyPressed) oldVel = transform->velocity;
                transform->velocity.Zero();
                keyPressed = false;
                break;
        }
    }
}
