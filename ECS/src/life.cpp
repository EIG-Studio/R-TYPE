/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** life
*/

#include "components.hpp"

Life::Life()
{
    this->m_lp = 100;
}

float Life::getLifePoint() const
{
    return this->m_lp;
}

void Life::setLifePoint(float mLp)
{
    this->m_lp = mLp;
}