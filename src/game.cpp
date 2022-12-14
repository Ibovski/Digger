#include "../headers/Game.h"
#include "../headers/Collision.h"

#include "../headers/Map.h"

Game &Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::Init(const char *title, int xpos, int ypos, int width, int height, bool fullscrean) {
    int flags = 0;
    if(fullscrean) flags = SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
//        /std::cout << "Subsystems installed\n";
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
//        if (window) std::cout << "Window created\n";
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//            std::cout << "Renderer created\n";
        }
        isRunning = true;
    }
    else return;
    Map::getInstance().Init();
    Map::loadMap("Maps/Map2",Parameters::HEIGHT,Parameters::WIDTH);
    createPlayer();
    createEnemy();
}

void Game::eventHandle() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {isRunning = false; break;}
        default: break;
    }
}
void Game::update() {
    createEnemy();
    if(!player->isActive()){
        lives--;
        restartGame();
    }
    for(int k = 0; k < movingEntities.size(); k++){
        if(movingEntities[k]->getComponent<CollisionComponent>().getTag() == "moneybag"){
            TransformComponent &moneyBagTransform = movingEntities[k]->getComponent<TransformComponent>();
            DestroyBag& moneyBag = movingEntities[k]->getComponent<DestroyBag>();
            if (moneyBagTransform.getPos().getX() % Parameters::PIXELS == 0 && moneyBagTransform.getPos().getY() % Parameters::PIXELS == 0) {
                int x = moneyBagTransform.getPos().getX() / Parameters::PIXELS;
                int y = moneyBagTransform.getPos().getY() / Parameters::PIXELS;

                if(y + 1 < Parameters::WIDTH && map[y+1][x] == 0) {
                    if(moneyBagTransform.velocity.getX() != 0) moneyBagTransform.velocity.setY(1);
                    else
                        if(!moneyBagTransform.isDelayed() && moneyBagTransform.velocity.getY() == 0)
                            moneyBagTransform.setDelay(Parameters::MONEYBAGFALL);
                }
                else {
                    if(y - moneyBag.getLastPosY() > 1) {
                       moneyBag.destroy();
                    }
                    map[moneyBag.getLastPosY()][moneyBag.getLastPosX()] -=static_cast<int> (moneyBag.entity->getComponent<TileComponent>().getTileID());
                    map[y][x] += static_cast<int> (moneyBag.entity->getComponent<TileComponent>().getTileID());
                    moneyBagTransform.velocity.setY(0) ;
                    moneyBag.setLastPosY(y);
                    moneyBag.setLastPosX(x);;
                }


                moneyBagTransform.velocity.setX(0);
            }
            if(moneyBag.isDestroyed()) movingEntities.erase(movingEntities.begin() + k);
        }
    }

    for(int k = 0; k < movingEntities.size(); k++) {
        CollisionComponent& curr = movingEntities[k]->getComponent<CollisionComponent>();

        for (int i = 0; i < colliders.size(); i++) {
            if (movingEntities[k]->isActive()){
                if(movingEntities[k]->hasComponent<ProjectileComponent>()){
                    ProjectileComponent& projectile = movingEntities[k]->getComponent<ProjectileComponent>();
                    if(projectile.isActive() && Collision::hasCollision(*projectile.getCollisionComponent(),*colliders[i])){
                        if(colliders[i]->getTag() == "dirt" || colliders[i]->getTag() == "moneybag")
                            projectile.destroy();
                        if(colliders[i]->getTag() == "monsters"){
                            projectile.destroy();
                            colliders[i]->entity->destroy();
                            score += TilePoints::enemyPoints;
                        }
                    }
                }
                if(colliders[i]->entity->isActive() && colliders[i]->entity->hasComponent<CollisionComponent>()) {
                    if (Collision::hasCollision(curr, *colliders[i])) {
                        if (curr.getTag() == "player" &&
                            (colliders[i]->getTag() == "dirt" || colliders[i]->getTag() == "diamond"
                             || colliders[i]->getTag() == "destroyedBag")) {

                            int x = colliders[i]->entity->getComponent<TransformComponent>().getPos().getX() / Parameters::PIXELS;
                            int y = colliders[i]->entity->getComponent<TransformComponent>().getPos().getY() / Parameters::PIXELS;
                            map[y][x] -= static_cast<int> (colliders[i]->entity->getComponent<TileComponent>().getTileID());
                            score += colliders[i]->entity->getComponent<SpriteComponent>().getPoints();
                            colliders[i]->entity->destroy();
                            colliders.erase(colliders.begin() + i);

                        }
                        if (curr.getTag() == "monsters" && (colliders[i]->getTag() == "diamond"
                                                            || colliders[i]->getTag() == "destroyedBag")) {
                            int x = colliders[i]->entity->getComponent<TransformComponent>().getPos().getX() / Parameters::PIXELS;
                            int y = colliders[i]->entity->getComponent<TransformComponent>().getPos().getY() / Parameters::PIXELS;
                            map[y][x] -= static_cast<int>(colliders[i]->entity->getComponent<TileComponent>().getTileID());
                            colliders[i]->entity->destroy();
                            colliders.erase(colliders.begin() + i);
                        }
                        if (curr.getTag() == "monsters" && colliders[i]->getTag() == "player") {
                            colliders[i]->entity->destroy();
                            colliders.erase(colliders.begin() + i);
                        }
                    }
                }

            }

        }
    }
    Map::getInstance().UpdateScoreBoard(score, lives);
    manager.refresh();
    manager.update();

}
void Game::render() {
    SDL_RenderClear(renderer);
    for(Entity* entity : manager.getGroup(groupMap)){
        entity->draw();
    }

    for(Entity* entity : manager.getGroup(groupPlayers)){
        entity->draw();
    }
    for(Entity* entity : manager.getGroup(groupEnemies)){
        entity->draw();
    }
    for(Entity* entity : manager.getGroup(groupRewards)){
        entity->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Game::AddTile(int xpos, int ypos, MapTilesID ID, unsigned int points,groupLabels group) {
    Entity* tile(manager.addEntity());
    tile->addComponent<TileComponent>(xpos,ypos,Parameters::PIXELS,Parameters::PIXELS,ID,points,group);
    if(ID == MapTilesID::moneyBagID) {
        tile->addComponent<DestroyBag>("img/destroyedBag.png",xpos / Parameters::PIXELS, ypos / Parameters::PIXELS);
        movingEntities.emplace_back(tile);
    }
}

void Game::createPlayer() {
    player = manager.addEntity();
    player->addComponent<TransformComponent>(Parameters::SCREEN_W / 2,10*Parameters::PIXELS,2,Parameters::PIXELS,Parameters::PIXELS);
    player->addComponent<SpriteComponent>("img/player1.png");
    player->addComponent<Keyboard>();
    player->addComponent<CollisionComponent>("player",0,Parameters::PIXELS,30,22);
    player->addComponent<ProjectileComponent>();
    player->addGroup(groupPlayers);
    movingEntities.emplace_back(player);
    for(auto& m : monsters){
        m->getComponent<ChaseComponent>().setTarget(player);
    }
}


void Game::createEnemy() {
    clearMonsters(false);
    Entity* monster = nullptr;
    if((delaySpawn == 0 || SDL_GetTicks() - delaySpawn >= Parameters::SPAWNDELAY)
    && enemiesLeft > 0) {
        delaySpawn = SDL_GetTicks();
        monster = manager.addEntity();
        monster->addComponent<TransformComponent>((Parameters::HEIGHT - 1) * Parameters::PIXELS, Parameters::PIXELS, 2, Parameters::PIXELS, Parameters::PIXELS);
        monster->addComponent<SpriteComponent>("img/Enemy2.png", TilePoints::enemyPoints);
        monster->addComponent<CollisionComponent>("monsters", (Parameters::HEIGHT - 1) * Parameters::PIXELS, Parameters::PIXELS, Parameters::PIXELS, Parameters::PIXELS);
        monster->addComponent<ChaseComponent>(player);
        monster->addGroup(groupEnemies);
        movingEntities.emplace_back(monster);
        monsters.emplace_back(monster);
        enemiesLeft--;

    }
}
void Game::clearMonsters(bool destroyAll){
    int i = 0;
    while(i < monsters.size()){
        if(destroyAll){
            monsters[i]->destroy();
        }
        if (!monsters[i]->isActive()){
            monsters.erase(monsters.begin() + i);
            enemiesLeft++;
        } else i++;
    }
}

void Game::restartGame() {
    if(lives >=0) {
        SDL_Delay(1000);
        createPlayer();
        clearMonsters(true);
        createEnemy();
    }
    else end();
}

void Game::end() {
    isRunning = false;
    SDL_Delay(2000);
}
