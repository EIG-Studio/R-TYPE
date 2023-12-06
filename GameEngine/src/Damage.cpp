/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Damage
*/

#include "components.hpp"

Damage::Damage(float damage)
{
    this->m_damage = damage;
}

float Damage::getDamage() const
{
    return this->m_damage;
}

void Damage::setDamage(int newDamage)
{
    this->m_damage = newDamage;
}
