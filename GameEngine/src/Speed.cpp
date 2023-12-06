/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Speed
*/

#include "components.hpp"

Speed::Speed(int speed)
{
    this->m_speed = speed;
}

int Speed::getSpeed() const
{
    return this->m_speed;
}

void Speed::setSpeed(int newSpeed)
{
    this->m_speed = newSpeed;
}
