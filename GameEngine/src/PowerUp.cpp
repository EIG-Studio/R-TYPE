/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** PowerUp
*/

#include "components.hpp"

PowerUp::PowerUp(bool isPowerUp)
{
    this->m_bluePojectile = isPowerUp;
}

bool PowerUp::getBlueProjectile() const
{
    return this->m_bluePojectile;
};
void PowerUp::setBlueProjectile(bool isPowerUp)
{
    this->m_bluePojectile = isPowerUp;
};