/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitBox
*/

#include "components.hpp"

HitBox::HitBox(std::pair<int, int> originPos, std::pair<int, int> endPos)
{
    this->_originPos.first = originPos.first;
    this->_originPos.second = originPos.second;
    this->_endPos.first = endPos.first;
    this->_endPos.second = endPos.second;
}

std::pair<int, int> HitBox::getOriginHitBoxPosition() const
{
    return this->_originPos;
}
std::pair<int, int> HitBox::getEndHitBoxPosition() const
{
    return this->_endPos;
}

void HitBox::setHitBoxPosition(std::pair<int, int> originPos, std::pair<int, int> endPos)
{
    this->_originPos.first = originPos.first;
    this->_originPos.second = originPos.second;
    this->_endPos.first = endPos.first;
    this->_endPos.second = endPos.second;
}
