/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Speed
*/

#include "components.hpp"

Speed::Speed(float speed)
{
    this->m_speed = speed;
}

float Speed::getSpeed() const
{
    return this->m_speed;
}

void Speed::setSpeed(float newSpeed)
{
    this->m_speed = newSpeed;
}
