/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Shooter
*/

#include "components.hpp"

Shooter::Shooter(bool isShooting)
{
    this->m_isShooting = isShooting;
}

bool Shooter::isShooter() const
{
    return this->m_isShooting;
}

void Shooter::setIsShooting(bool isShooting)
{
    this->m_isShooting = isShooting;
}
