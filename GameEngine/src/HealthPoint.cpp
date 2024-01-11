/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** life
*/

#include "components.hpp"

HealthPoint::HealthPoint(float hp)
{
    this->m_lp = hp;
}

float HealthPoint::getHealthPoint() const
{
    return this->m_lp;
}

void HealthPoint::setHealthPoint(float mLp)
{
    this->m_lp = mLp;
}