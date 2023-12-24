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
    ID newID;

    for (auto & mEntitie : m_entities) {
        newID = any_cast<ID>(mEntitie.mComponents[0]);
        if (newID.getID() == id)
            entity = mEntitie;
    }

    return entity;
}
