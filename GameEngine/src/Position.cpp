/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#include "components.hpp"

#include <iostream>
Position::Position(std::pair<int, int> originPos)
{
    this->m_pos.first = originPos.first;
    this->m_pos.second = originPos.second;
}

std::pair<int, int> Position::getPosition() const
{
    return this->m_pos;
};

void Position::setPosition(std::pair<int, int> newPos)
{
    this->m_pos.first = newPos.first;
    this->m_pos.second = newPos.second;
};
