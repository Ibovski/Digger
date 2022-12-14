#include "../headers/ECS.h"
#include "../headers/Game.h"
#include <algorithm>
void Entity::addGroup(Group group) {
    groupBitSet[group] = true;
    manager.addToGroup(this,group);
}

Entity::Entity(Manager &manager) : manager(manager) {}

void Entity::update() {
    for(auto& c : components) c->update();
}

void Entity::draw() {
    for(auto& c : components) c->draw();
}

bool Entity::isActive() const {
    if(this == nullptr)
        return false;
    return active;
}

void Entity::destroy() {
    active = false;
}

Entity::~Entity() {
    destroy();
}

void Entity::removeGroup(Group group) {
    groupBitSet[group] = false;
}

// ---------------------------------------------

void Manager::update() {
    for(auto& e : entities) e->update();
}

void Manager::draw() {
    for(auto& e : entities) e->draw();;
}

void Manager::refresh() {

    int i = 0;
    while(i < Game::getInstance().colliders.size()){
        if (!Game::getInstance().colliders[i]->entity->isActive()) {
            std::swap(Game::getInstance().colliders[i], Game::getInstance().colliders.back());
            Game::getInstance().colliders.pop_back();
        }
        else i++;
    }
    i = 0;
    while(i < Game::getInstance().movingEntities.size()) {
        if (!Game::getInstance().movingEntities[i]->isActive()) {
            std::swap(Game::getInstance().movingEntities[i], Game::getInstance().movingEntities.back());
            Game::getInstance().movingEntities.pop_back();
        } else i++;
    }
    for(Group j = 0; j < maxGroups; j++){
        i = 0;
        while(i < groupedEntitiesArr[j].size()){
            if(!groupedEntitiesArr[j][i]->isActive() || !groupedEntitiesArr[j][i]->hasGroup(j)) {
                std::swap(groupedEntitiesArr[j][i], groupedEntitiesArr[j].back());
                groupedEntitiesArr[j].pop_back();
            }
            else i++;
        }
    }
    i = 0;
    while(i < entities.size()){
        if(!entities[i]->isActive())
        {
            if(entities[i].get() == Game::getInstance().player) Game::getInstance().player = nullptr;
            for(int j = 0; j < Game::getInstance().monsters.size(); j++){
                if(entities[i].get() == Game::getInstance().monsters[j]) Game::getInstance().monsters[j] = nullptr;
            }
            std::swap(entities[i],entities.back());
            entities.pop_back();
        }
        else i++;
    }
}

void Manager::addToGroup(Entity *e, Group gr){
    groupedEntitiesArr[gr].emplace_back(e);
}

std::vector<Entity *> &Manager::getGroup(Group group){
    return groupedEntitiesArr[group];
}

Entity* Manager::addEntity(){
    Entity *e = new Entity(*this);
    std::unique_ptr<Entity> Ptr{e};
    entities.emplace_back(std::move(Ptr));
    return e;
}