/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** registry
*/

#pragma once
#include "entities.hpp"

#include <vector>

class Registry
{
public:
    Registry() = default;
    ~Registry() = default;

private:
    std::vector<Entity> m_availableEntities;
};
