/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#include "components.hpp"

Position::Position(std::pair<int, int> originPos)
{
    this->_pos.first = originPos.first;
    this->_pos.second = originPos.second;
}

std::pair<int, int> Position::getPosition() const
{
    return this->_pos;
};

void Position::setPosition(std::pair<int, int> newPos)
{
    this->_pos.first = newPos.first;
    this->_pos.second = newPos.second;
};

