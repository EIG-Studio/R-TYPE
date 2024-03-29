#include "Systems.hpp"
#include "components.hpp"
#include "entities.hpp"

#include <any>
#include <iostream>

#include <cassert>
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

    for (auto& mEntitie : m_entities) {
        size_t entityID = any_cast<ID>(mEntitie.mComponents[0]).getID();
        if (entityID == id) {
            std::cout << "Destroying entity with ID: " << entityID << std::endl;
            toDelete.push_back(id);
            return;
        }
    }

    std::cerr << "Entity with ID " << id << " not found for destruction." << std::endl;
}

// std::string Registry::systemsManager()
// {
//     if (!m_entities.empty())
//         for (const Entity& entity : m_entities) {
//             // shootingSystem(entity, *this);
//             movementSystem(entity, *this);
//             collisionSystem(entity, m_entities, *this);
//             deathSystem(entity, *this);
//         }
//     for (auto& id : toDelete) {
//         this->deleteById(id);
//     }
//     toDelete.clear();
//     return "Hello";
// }

std::vector<std::string> Registry::systemsManager()
{
    std::vector<std::string> messages;

    if (m_entities.empty())
        return messages;
    bool score = hasScore();
    for (const Entity& entity : m_entities) {
        std::string message;
        // shootingSystem(entity, *this);
        message = movementSystem(entity, *this);
        if (!message.empty()) {
            messages.push_back(message);
            message = "";
        }
        message = collisionSystem(entity, m_entities, *this);
        if (!message.empty()) {
            messages.push_back(message);
            message = "";
        }
        message = deathSystem(entity, *this);
        if (!message.empty()) {
            messages.push_back(message);
            message = "";
        }
    }
    int newScore = 0;
    for (auto& id : toDelete) {
        Entity entity = getEntity(id);
        if (hasComponent(entity, Type{}) && getComponent(entity, Type{}).getEntityType() == EntityType::Enemy) {
            newScore += 1;
        }
        this->deleteById(id);
        messages.push_back("DELETE " + std::to_string(id));
    }
    if (score and newScore > 0) {
        Entity score = getFirstEntityOfType(EntityType::HUD);
        ID scoreId = getComponent(score, ID{});
        ScorePoint& scorePoint = getComponent(score, ScorePoint{});
        scorePoint.setScorePoint((scorePoint.getScorePoint() + newScore));
        setEntity(score, scoreId.getID());
        messages.push_back("SCORE " + std::to_string(scorePoint.getScorePoint()) + "|");
    }
    toDelete.clear();
    return messages;
}

std::string Registry::systemsManager(sf::RenderWindow& window)
{
    if (!m_entities.empty())
        for (const Entity& entity : m_entities) {
            // movementSystem(entity, *this);
            renderSystem(entity, *this, window);
        }
    return "Hello";
}

Entity Registry::getEntity(size_t id)
{
    Entity entity;
    size_t otherID;

    for (auto& mEntitie : m_entities) {
        otherID = std::any_cast<size_t>(this->getComponent(mEntitie, ID{}).getID());
        if (otherID == id) {
            return mEntitie;
        }
    }
    return entity;
}

bool Registry::hasEntity(size_t id)
{
    size_t otherID;

    for (auto& entity : m_entities) {
        otherID = std::any_cast<size_t>(this->getComponent(entity, ID{}).getID());
        if (otherID == id) {
            return true;
        }
    }
    return false;
}

bool Registry::hasEntityType(Type type)
{
    Type otherType{};

    for (auto& entity : m_entities) {
        if (hasComponent(entity, Type{})) {
            otherType = getComponent(entity, Type{});
            if (otherType.getEntityType() == type.getEntityType()) {
                return true;
            }
        }
    }
    return false;
}

void Registry::setEntity(Entity& entityToCopy, int id)
{
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, ID{})) {
            ID& idComponent = this->getComponent(entity, ID{});
            if (idComponent.getID() == id) {
                entity = entityToCopy;
                return;
            }
        }
    }
}

Entity Registry::getFirstEntityOfType(EntityType type)
{
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == type) {
                return entity;
            }
        }
    }
    throw std::runtime_error("No entity of this type found\n");
}

bool Registry::hasScore()
{
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == EntityType::HUD) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Entity> Registry::getListEntities(EntityType type)
{
    std::vector<Entity> entities;

    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == type) {
                entities.push_back(entity);
            }
        }
    }
    return entities;
}

void Registry::deleteById(int id)
{
    std::vector<Entity> entities;
    std::vector<Entity> tmpEntities;

    for (auto& entity : m_entities) {
        if (id == this->getComponent(entity, ID{}).getID()) {
            continue;
        } else {
            tmpEntities.push_back(entity);
        }
    }
    m_entities = tmpEntities;
}


std::vector<Entity> Registry::getListEntities()
{
    std::vector<Entity> enemies;
    enemies.reserve(m_entities.size());
    for (auto& entity : m_entities) {
        enemies.push_back(entity);
    }
    return enemies;
}

void Registry::destroyEnemy(std::vector<Entity> enemyList)
{
    Position enemyPos = this->getComponent(enemyList[0], Position{});
    std::pair<float, float> pairPos = enemyPos.getPosition();
    std::cout << "ENEMY POS X: " << pairPos.first << std::endl;
    std::cout << "ENEMY POS Y: " << pairPos.second << std::endl;
}
