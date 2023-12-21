/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Type
*/

#include "components.hpp"

EntityType Type::getEntityType() const
{
    return this->m_entityType;
}

void Type::setEntityType(EntityType entityType)
{
    this->m_entityType = entityType;
}
