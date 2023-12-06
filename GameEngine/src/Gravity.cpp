/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Gravity
*/

#include "components.hpp"

Gravity::Gravity(float gravity, bool isGravity)
{
    this->_Gravity = gravity;
    this->_isGravity = isGravity;
}

float Gravity::getGravity() const
{
    return this->_Gravity;
}

bool Gravity::isGravity() const
{
    return this->_isGravity;
}

void Gravity::setGravity(float newGravity)
{
    this->_Gravity = newGravity;
}

void Gravity::setIsGravity(bool isGravity)
{
    this->_isGravity = isGravity;
}
