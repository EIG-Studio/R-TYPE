/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitBox
*/

#include "components.hpp"

HitBox::HitBox(std::pair<int, int> originPos, std::pair<int, int> endPos)
{
    this->m_originPos.first  = originPos.first;
    this->m_originPos.second = originPos.second;
    this->m_endPos.first     = endPos.first;
    this->m_endPos.second    = endPos.second;
}

std::pair<int, int> HitBox::getOriginHitBoxPosition() const
{
    return this->m_originPos;
}
std::pair<int, int> HitBox::getEndHitBoxPosition() const
{
    return this->m_endPos;
}

void HitBox::setHitBoxPosition(std::pair<int, int> originPos, std::pair<int, int> endPos)
{
    this->m_originPos.first  = originPos.first;
    this->m_originPos.second = originPos.second;
    this->m_endPos.first     = endPos.first;
    this->m_endPos.second    = endPos.second;
}
