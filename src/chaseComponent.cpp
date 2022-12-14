#include "../headers/ChaseComponent.h"
#include <queue>

void ChaseComponent::shortestPath(Vector2D pos) {
    clearDist();
    pos = pos/Parameters::PIXELS;
    pos.setPos(pos.getY(),pos.getX());

    dist[pos.getX()][pos.getY()] = 0;
    std::queue<Vector2D> bfs;
    bfs.push(pos);
    while(!bfs.empty()){
        Vector2D currPos = bfs.front();
        bfs.pop();
        int x = currPos.getX();
        int y = currPos.getY();
        visited[x][y] = true;

        if(y+1 < Parameters::HEIGHT && Game::getInstance().map[x][y+1] < static_cast<int> (MapTilesID::dirtID)){
            dist[x][y+1] = (dist[x][y+1] == -1 ? dist[x][y]+1 : std::min(dist[x][y+1],dist[x][y]+1));
            if(!visited[x][y+1])
                bfs.push(Vector2D(x,y+1));
        }
        if(y-1 >=0 && Game::getInstance().map[x][y-1] < static_cast<int> (MapTilesID::dirtID)){
            dist[x][y-1] = (dist[x][y-1] == -1 ? dist[x][y]+1 : std::min(dist[x][y-1],dist[x][y]+1));
            if(!visited[x][y-1])
                bfs.push(Vector2D(x,y-1));
        }
        if(x+1 < Parameters::WIDTH && Game::getInstance().map[x+1][y] < static_cast<int> (MapTilesID::dirtID)){
            dist[x+1][y] = (dist[x+1][y] == -1 ? dist[x][y]+1 : std::min(dist[x+1][y],dist[x][y]+1));
            if(!visited[x+1][y])
                bfs.push(Vector2D(x+1,y));
        }
        if(x-1 >= 0  && Game::getInstance().map[x-1][y] < static_cast<int> (MapTilesID::dirtID)){
            dist[x-1][y] = (dist[x-1][y] == -1 ? dist[x][y]+1 : std::min(dist[x-1][y],dist[x][y]+1));
            if(!visited[x-1][y])
                bfs.push(Vector2D(x-1,y));
        }
    }
}

void ChaseComponent::clearDist() {
    for(int i = 0; i < Parameters::WIDTH; i++)
        for(int j = 0; j < Parameters::HEIGHT; j++) {
            dist[i][j] = -1;
            visited[i][j] = false;
        }
}


ChaseComponent::ChaseComponent(Entity* target) : target(target) {
    clearDist();
}

void ChaseComponent::update() {
    if(target->hasComponent<TransformComponent>())
        shortestPath(target->getComponent<TransformComponent>().getPos());
    move();
}

void ChaseComponent::move() {
    TransformComponent& currTransform = entity->getComponent<TransformComponent>();
    if(currTransform.getPos().getX() % Parameters::PIXELS != 0 || currTransform.getPos().getY() % Parameters::PIXELS != 0) return;
    int x = currTransform.getPos().getY() / Parameters::PIXELS;
    int y = currTransform.getPos().getX() / Parameters::PIXELS;
    if(y+1 < Parameters::HEIGHT && dist[x][y+1] < dist[x][y] && dist[x][y+1] != -1){
        currTransform.velocity.Zero();
        currTransform.velocity.setX(1);
    }
    else
    if(y-1 >=0 && dist[x][y-1] < dist[x][y] && dist[x][y-1] != -1){
        currTransform.velocity.Zero();
        currTransform.velocity.setX(-1);
    }
    else
    if(x+1 < Parameters::WIDTH && dist[x+1][y] < dist[x][y] && dist[x+1][y] != -1){
        currTransform.velocity.Zero();
        currTransform.velocity.setY(1);
    }
    else
    if(x-1 < Parameters::WIDTH && dist[x-1][y] < dist[x][y] && dist[x-1][y] != -1){
        currTransform.velocity.Zero();
        currTransform.velocity.setY(-1);
    } else{
        currTransform.velocity.Zero();
    }
}

void ChaseComponent::setTarget(Entity *_target) {
    this->target = _target;
}
