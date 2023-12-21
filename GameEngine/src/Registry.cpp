#include "entities.hpp"
#include <any>

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
    for (auto & mComponent : entity.mComponents) {
        if ((mComponent).type() == component.type())
            return std::any_cast<T&>(mComponent);
    }
    throw std::runtime_error("Component does not exist");
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
    ID newID = any_cast<ID>(entity.mComponents[0]);
    size_t id = newID.getID();

    assert(!m_entities.empty());
    for (size_t i = 0; i < m_entities.size(); i++) {
        newID = any_cast<ID>(m_entities[i].mComponents[0]);
        if (newID.getID() == id)
            m_entities.erase(m_entities.begin() + i);
    }
}
