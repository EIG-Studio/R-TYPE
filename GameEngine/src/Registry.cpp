#include "Systems.hpp"
#include "entities.hpp"

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
    size_t entityID;

    assert(!m_entities.empty());

    for (size_t i = 0; i < m_entities.size(); i++) {
        entityID = any_cast<ID>(m_entities[i].mComponents[0]).getID();
        std::cout << "Destroying entity with ID: " << entityID << std::endl;
        if (entityID == id)
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

Entity Registry::getPlayer()
{
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            if (typeComponent.getEntityType() == EntityType::Player) {
                return entity;
            }
        }
    }
    throw std::runtime_error("No Player entity found\n");
}

Entity Registry::getFirstEnemy()
{
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

std::vector<Entity> Registry::getListEnemies()
{
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

std::vector<Entity> Registry::getListPlayers()
{
    std::vector<Entity> players;
    for (auto& player : m_entities) {
        if (this->hasComponent(player, Type{})) {
            Type& typeComponent = this->getComponent(player, Type{});
            if (typeComponent.getEntityType() == EntityType::Player) {
                players.push_back(player);
            }
        }
    }
    return players;
}

std::vector<Entity> Registry::getListPlayersProjectile()
{
    std::vector<Entity> playersProjectiles;
    for (auto& playerProjectile : m_entities) {
        if (this->hasComponent(playerProjectile, Type{})) {
            Type& typeComponent = this->getComponent(playerProjectile, Type{});
            if (typeComponent.getEntityType() == EntityType::Player_Projectile) {
                playersProjectiles.push_back(playerProjectile);
            }
        }
    }
    return playersProjectiles;
}

std::vector<Entity> Registry::deletePlayersProjectile(int id)
{
    std::vector<Entity> playersProjectiles;
    for (auto& playerProjectile : m_entities) {
        if (this->hasComponent(playerProjectile, Type{})) {
            Type& typeComponent = this->getComponent(playerProjectile, Type{});
            if (typeComponent.getEntityType() == EntityType::Player_Projectile) {
                if (id == this->getComponent(playerProjectile, ID{}).getID()) {
                    this->destroyEntity(playerProjectile);
                }
            }
        }
    }
    return playersProjectiles;
}

std::vector<Entity> Registry::getListEntities()
{
    std::vector<Entity> enemies;
    for (auto& entity : m_entities) {
        if (this->hasComponent(entity, Type{})) {
            Type& typeComponent = this->getComponent(entity, Type{});
            enemies.push_back(entity);
        }
    }
    return enemies;
}

void Registry::destroyEnnemy(std::vector<Entity> ennemyList)
{
    Position ennemyPos = this->getComponent(ennemyList[0], Position{});
    std::pair<float, float> pairPos = ennemyPos.getPosition();
    std::cout << "ENNEMY POS X: " << pairPos.first << std::endl;
    std::cout << "ENNEMY POS Y: " << pairPos.second << std::endl;
    //if (playerPosY <= ennemyPosY + 40 && playerPosY >= ennemyPosY - 15) {
    //    std::cout << "BOOM !!!!" << std::endl;
    //}

    //sf::Vertex line[] = {sf::Vertex(sf::Vector2f(10, ennemyPosY + 20)), sf::Vertex(sf::Vector2f(10, ennemyPosY - 30))};
}
