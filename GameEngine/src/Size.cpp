/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Size
*/

#include "components.hpp"

Size::Size(std::pair<float, float> originSize)
{
    this->m_size.first = originSize.first;
    this->m_size.second = originSize.second;
}

std::pair<float, float> Size::getSize() const
{
    return this->m_size;
}

void Size::setSize(std::pair<float, float> newSize)
{
    this->m_size.first = newSize.first;
    this->m_size.second = newSize.second;
}
