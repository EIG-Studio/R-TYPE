/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Damage
*/

#include "components.hpp"

Damage::Damage(float damage)
{
    this->_Damage = damage;
}

float Damage::getDamage() const
{
    return this->_Damage;
}

void Damage::setDamage(int newDamage)
{
    this->_Damage = newDamage;
}
