/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** HitBox
*/

#include "components.hpp"

HitBox::HitBox(std::pair<float, float> originPos, std::pair<float, float> size)
{
    this->m_originPos.first = originPos.first;
    this->m_originPos.second = originPos.second;
    this->m_size.first = size.first;
    this->m_size.second = size.second;
}

std::pair<float, float> HitBox::getOriPos() const
{
    return this->m_originPos;
}
std::pair<float, float> HitBox::getSize() const
{
    return this->m_size;
}

void HitBox::setHitBoxPosition(std::pair<float, float> originPos, std::pair<float, float> size)
{
    this->m_originPos.first = originPos.first;
    this->m_originPos.second = originPos.second;
    this->m_size.first = size.first;
    this->m_size.second = size.second;
}
