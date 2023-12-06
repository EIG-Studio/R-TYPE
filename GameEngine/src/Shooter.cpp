/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Shooter
*/

#include "components.hpp"

Shooter::Shooter(bool isShooting)
{
    this->_isShooting = isShooting;
}

bool Shooter::isShooter() const
{
    return this->_isShooting;
}

void Shooter::setIsShooting(bool isShooting)
{
    this->_isShooting = isShooting;
}
