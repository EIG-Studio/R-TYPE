#include "entities.hpp"

template <typename T>
void Registry::addComponent(Entity entity, T component)
{
    entity.mComponents.push_back(component);
}

void Registry::destroyEntity(Entity entity)
{

}
