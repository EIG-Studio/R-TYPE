#include "entities.hpp"

#include <cstddef>

template <typename T>
void Registry::addComponent(Entity entity, T component)
{
    entity.mComponents.push_back(component);
}

template <typename T>
void Registry::removeComponent(Entity entity, T component)
{
    int index = entity.mComponents[component].has_value();
    entity.mComponents.erase(entity.mComponents.begin() + index);
}

template <typename T>
T& Registry::getComponent(Entity& entity, T component)
{
    for (size_t i = 0; i < entity.mComponents.size(); i++) {
        if (entity.mComponents[i].has_value() == component)
            return std::any_cast<T&>(entity.mComponents[i]);
    }

    if (!entity.mComponents[component].has_value())
        throw std::runtime_error("Component does not exist");
    return std::any_cast<T&>(entity.mComponents[component]);
}

Entity Registry::createEntity()
{
    Entity newEntity = Entity();
    ID newID = ID(this->m_id);

    addComponent(newEntity, newID);
    m_entities.push_back(newEntity);
    this->m_id += 1;
    return newEntity;
}

void Registry::destroyEntity(Entity entity)
{
    assert(!m_entities.empty());
    // get id de l'entity en question
    // size_t id = entity.mComponents
    // m_entities.back();
    // loop on entities to get the entity with id wanted then erase the entity with the id asked
    // m_entities.();
}
