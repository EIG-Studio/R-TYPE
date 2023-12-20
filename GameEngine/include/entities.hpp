/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"

#include <SFML/Window.hpp>

#include <SFML/System.hpp>

#include <memory>
#include <unordered_map>
#include <vector>
#include <any>

#include <cassert>
#include <cstdint>

extern "C"
{
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();
}

class Entity
{
public:
    Entity();
    ~Entity();

    std::vector<std::any> mComponents;
private:
};

class EntityManager
{
public:
    EntityManager();
    Entity createEntity();
    template <typename... Components>
    EntityManager(Components&&... components);

    template <typename Component>
    Component* getComponent() const;

    template <typename Component, typename... Rest>
    void addComponents(Component&& component, Rest&&... rest);
    void destroyEntity(Entity entity);

private:
    std::vector<Entity> m_entities;
    template <typename Component>
    void addComponent(Component&& component);
};

/********-Registry-******/
class Registry
{
public:
    Registry() = default;
    ~Registry() = default;
    Entity createEntity();
    void destroyEntity(Entity entity);
    template<typename T>
    void addComponent(Entity entity, T component);
    template<typename T>
    void removeComponent(Entity entity, T component);
    template<typename T>    
    T& getComponent(Entity entity);

private:
    template<typename T>
    std::unordered_map<Entity, T>& getComponentStorage() {
        static std::unordered_map<Entity, T> storage;
        return storage;
    }
    std::vector<Entity> m_entities;
};
