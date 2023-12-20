#include "entities.hpp"

template <typename T>
void Registry::addComponent(Entity entity, T component)
{
    entity.mComponents.push_back(component);
}

template <typename T>
void Registry::removeComponent(Entity entity, T component)
{
    int index = std::any(entity.mComponents[component]).has_value();
    entity.mComponents.erase(entity.mComponents.begin() + index);
}
