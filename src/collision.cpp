#include <iostream>
#include "../headers/Collision.h"


bool Collision::hasCollision(const SDL_Rect &recA, const SDL_Rect &recB) {
    if(recA.x + recA.w > recB.x &&
       recB.x + recB.w > recA.x &&
       recA.y + recA.h > recB.y &&
       recB.y + recB.h > recA.y)
        return true;

    return false;
}

bool Collision::hasCollision(const CollisionComponent &colA, const CollisionComponent &colB) {
    if(&colA != &colB && hasCollision(colA.getCollider(),colB.getCollider())) {
        if ((colA.getTag() == "player" || colA.getTag() == "monsters") && colB.getTag() == "moneybag"){
            TransformComponent& colAtr = colA.entity->getComponent<TransformComponent>();
            TransformComponent& colBtr = colB.entity->getComponent<TransformComponent>();
            if(colBtr.velocity.getY() == 0 && colAtr.isDead()) colAtr.entity->destroy();
            if(colBtr.velocity.getY() == 1) {
                colAtr.setPos(colBtr.getPos());
                colAtr.setDeath(true);
            }
            else {
                colBtr.velocity = Vector2D(1, 0) * colAtr.velocity;
                if (colAtr.velocity.getX() == 0) {
                    Vector2D changePos = colAtr.getPos();
                    while (changePos.getY() % Parameters::PIXELS != 0 && colAtr.velocity.getY() != 0)
                        changePos.setY(changePos.getY() -colAtr.getSpeed() * colAtr.velocity.getY());
                    changePos.setY(changePos.getY() -colAtr.getSpeed() * colAtr.velocity.getY());
                    colAtr.setPos(changePos);
                }
            }
        }
        if(colA.getTag() == "moneybag" && colB.getTag() == "moneybag"){
            TransformComponent& colAtr = colA.entity->getComponent<TransformComponent>();
            TransformComponent& colBtr = colB.entity->getComponent<TransformComponent>();
            Vector2D diff = (colAtr.getPos() - colBtr.getPos()) * colAtr.velocity;
            if(colBtr.velocity == Vector2D(0,0) && Vector2D(0,0) >= diff)
                colBtr.velocity = colAtr.velocity;

        }
        return true;
    }
    return false;
}
