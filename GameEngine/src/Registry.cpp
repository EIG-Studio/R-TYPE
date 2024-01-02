#include "entities.hpp"
#include "Systems.hpp"
#include <any>

#include <cstddef>

Entity Registry::createEntity()
{
    Entity newEntity = Entity();
    ID newID = ID(this->m_id);

    newEntity.mComponents.emplace_back(newID);
    m_entities.push_back(newEntity);
    this->m_id += 1;
    return newEntity;
}

Entity Registry::createEntityWithID(int customID)
{
    Entity newEntity = Entity();
    ID newID = ID(customID);

    newEntity.mComponents.emplace_back(newID);
    m_entities.push_back(newEntity);
    return newEntity;
}


void Registry::destroyEntity(Entity entity)
{
    ID newID = any_cast<ID>(entity.mComponents[0]);
    size_t id = newID.getID();

    assert(!m_entities.empty());

    for (size_t i = 0; i < m_entities.size(); i++) {
        newID = any_cast<ID>(m_entities[i].mComponents[0]);
        if (newID.getID() == id)
            m_entities.erase(m_entities.begin() + i);
    }
}
#include <iostream>

std::string Registry::systemsManager(sf::RenderWindow& window)
{
    if (!m_entities.empty())
        for (const Entity& entity : m_entities) {
            shootingSystem(entity, *this);
            deathSystem(entity, *this);
            movementSystem(entity, *this);
            collisionSystem(entity, m_entities, *this);
            renderSystem(entity, *this, window);
        }
    return "Hello";
}

Entity Registry::getEntity(size_t id)
{
    Entity entity;
    size_t otherID;

    for (auto & mEntitie : m_entities) {
        otherID = std::any_cast<size_t>(this->getComponent(mEntitie, ID{}).getID());
        if (otherID == id) {
            return mEntitie;
        }
    }

    return entity;
}

Entity Registry::getPlayer() {
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == EntityType::Player) {
                return entity;
            }
        }
    }
    throw std::runtime_error("No Player entity found");
}

Entity Registry::getFirstEnemy() {
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == EntityType::Enemy) {
                return entity;
            }
        }
    }
    throw std::runtime_error("No Ennemy entity found");
}

std::vector<Entity> Registry::getListEnemies() {
    std::vector<Entity> enemies;
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == EntityType::Enemy) {
                enemies.push_back(entity);
            }
        }
    }
    return enemies;
}
