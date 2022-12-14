#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <memory>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

/**
 * Inline function to return the componentID starting from 0.
 * @return ComponentTypeID
 */
inline ComponentID getNewComponentTypeID(){
    static ComponentID lastID = 0;
    return lastID++;
}
/**
 * Template inline function to get the ComponentTypeID
 * @tparam T The Component type we need the ID for.
 * @return The Component's ID we need.
 */
template<typename T> inline ComponentID getComponentTypeID(){
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 16; /**< The maximum components we can create */
constexpr Group maxGroups = 16; /**< The maximum groups we can divide all the objects */

/**
 * An interface class in order to implement the EntityComponent system.
 */
class Component{
public:
    Entity* entity; /**< A pointer to entity this component belongs */
    virtual void init() = 0; /**< A pure virtual function for initialising the component */
    virtual void update() = 0; /**< A pure virtual function for updating the component */
    virtual void draw(){}; /**< A virtual function for drawing the component */
    virtual ~Component() = default; /**< A virtual destructor for the component */

};

/**
 * The entity class in order to implement the EntityComponent system.
 */
class Entity{
private:
    Manager& manager; /**< A reference to the manager this entity will be added */
    bool active = true; /**< Tells if the entity is active */
    std::vector<std::unique_ptr<Component>> components; /**< A std::vector of unique_ptr<Component> to contain all the components of the entity */
    std::array<Component*, maxComponents> componentsArr; /**< An std::array to contain all the types of the entity's components */
    std::bitset<maxComponents> componentsBitSet; /**< A std::bitset for easy check whether we have a certain type of component */
    std::bitset<maxGroups> groupBitSet; /**< A std::bitset for easy check in which group the entity belongs to */

public:
    explicit Entity(Manager& manager);
    ~Entity();
    /**
     * Update all the components.
     */
    void update();
    /**
     * Draw all the components.
     */
    void draw();
    /**
     * Check if the entity is active.
     * @return active.
     */
    bool isActive() const;
    /**
     * Make the active false.
     */
    void destroy();
    /**
     * Add the entity to certain group.
     * @param group The group we will add our entity to.
     */
    void addGroup(Group group);
    /**
     * Remove the entity from certain group.
     * @param group The group we will remove our entity from.
     */
    void removeGroup(Group group);
    /**
     * A template function to check if our entity has a certain component.
     * @tparam T The component type we want to check.
     * @return True if it has the T component type. False otherwise.
     */
    template<typename T>
    bool hasComponent() const {
        return componentsBitSet[getComponentTypeID<T>()];
    }
    /**
     * Check if our entity is in a certain group.
     * @param  The group type we want to check.
     * @return True if it is in the group type. False otherwise.
     */
    bool hasGroup(Group group) const {
        return groupBitSet[group];
    }
    /**
     * A template function for adding a new component to our entity.
     * @tparam T The component type we want to add.
     * @tparam tArgs The component type's arguments.
     * @param Args The component arguments
     * @return none
     */
    template<typename T, typename... tArgs>
    void addComponent(tArgs &&... Args) {
        T* c(new T(std::forward<tArgs>(Args)...));
        c->entity = this;
        std::unique_ptr<Component> Ptr{c};
        components.emplace_back(std::move(Ptr));

        componentsArr[getComponentTypeID<T>()] = c;
        componentsBitSet[getComponentTypeID<T>()] = true;
        c->init();
    }
    /**
     * Get the a certain component from our entity.
     * @tparam T The component type.
     * @return Reference to the component type.
     */
    template<typename T>
    T &getComponent() const {
        auto ptr (componentsArr[getComponentTypeID<T>()]);
        return *static_cast<T*> (ptr);
    }

};

/**
 * A manager class which will hold all the entities.
 * It will call all the update and draw functions they have.
 */
class Manager{
private:
    std::vector<std::unique_ptr<Entity>> entities; /**< A std::vector of unique_ptr to contain all the entities */
    std::array<std::vector<Entity*>,maxGroups> groupedEntitiesArr; /**< A std::array of Entity pointers to contain the entities in common groups*/
public:
    /**
     * Update function for all the entities.
     */
    void update();
    /**
     * Draw function for all the entities.
     */
    void draw();
    /**
     * A function which will delete the entities which are not active.
     */
    void refresh();
    /**
     * Adding an entity to a certain group.
     * @param e The entity we want to add.
     * @param gr The group we want to add the entity.
     */
    void addToGroup(Entity* e, Group gr);
    /**
     * A function to get all the entities which belong to a certain group.
     * @param group The entity group we want to take.
     * @return A std::vector<Entity*>&
     */
    std::vector<Entity*>& getGroup(Group group);
    /**
     * A function to create new entity and add it to the manager.
     * @return A pointer to the new entity.
     */
    Entity* addEntity();
};