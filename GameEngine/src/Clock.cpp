/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** Clock
*/

#include "components.hpp"

float Clock::getClock()
{
    sf::Time elapsed = m_clock.getElapsedTime();
    return elapsed.asSeconds();
}

void Clock::restartClock()
{
    m_clock.restart();
}