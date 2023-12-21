/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Velocity
*/

#include "components.hpp"

Velocity::Velocity()
{
    this->m_velo.first = 0;
    this->m_velo.second = 0;
}

std::pair<int, int> Velocity::getVelocity() const
{
    return this->m_velo;
}

void Velocity::setVelocity(int x, int y)
{
    this->m_velo.first = x;
    this->m_velo.second = y;
}
