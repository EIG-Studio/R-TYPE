/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Speed
*/

#include "components.hpp"

Speed::Speed(int speed)
{
    this->_Speed = speed;
}

int Speed::getSpeed() const
{
    return this->_Speed;
}

void Speed::setSpeed(int newSpeed)
{
    this->_Speed = newSpeed;
}
