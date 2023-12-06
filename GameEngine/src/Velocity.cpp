/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Velocity
*/

#include "components.hpp"

Velocity::Velocity()
{
    this->_velo.first = 0;
    this->_velo.second = 0;
}

std::pair<int, int> Velocity::getVelocity() const
{
    return this->_velo;
}

void Velocity::setVelocity(int x, int y)
{
    this->_velo.first = x;
    this->_velo.second = y;
}


