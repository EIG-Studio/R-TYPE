/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** life
*/

#include "components.hpp"

HealthPoint::HealthPoint()
{
    this->m_lp = 100;
}

float HealthPoint::getHealthPoint() const
{
    return this->m_lp;
}

void HealthPoint::setHealthPoint(float mLp)
{
    this->m_lp = mLp;
}
