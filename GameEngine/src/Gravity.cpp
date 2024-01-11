/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Gravity
*/

#include "components.hpp"

Gravity::Gravity(float gravity, bool isGravity)
{
    this->m_gravity = gravity;
    this->m_isGravity = isGravity;
}

float Gravity::getGravity() const
{
    return this->m_gravity;
}

bool Gravity::isGravity() const
{
    return this->m_isGravity;
}

void Gravity::setGravity(float newGravity)
{
    this->m_gravity = newGravity;
}

void Gravity::setIsGravity(bool isGravity)
{
    this->m_isGravity = isGravity;
}
