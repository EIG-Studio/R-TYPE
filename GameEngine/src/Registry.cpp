#include "entities.hpp"

template <typename T>
void addComponent(Entity& entity, T component)
{
    entity.mComponents.push_back(component);
}
