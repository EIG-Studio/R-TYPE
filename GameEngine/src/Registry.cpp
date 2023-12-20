#include "entities.hpp"

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
T& Registry::getComponent(Entity &entity, T component)
{
    if (!entity.mComponents[component].has_value())
        throw std::runtime_error("Component does not exist");
    return std::any_cast<T&>(entity.mComponents[component]);
}

extern "C++" Registry* factory()
{
    return new Registry();
}