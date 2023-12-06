/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Size
*/

#include "components.hpp"

Size::Size(float size)
{
    this->m_size = size;
}

float Size::getSize() const
{
    return this->m_size;
}

void Size::setSize(int newSize)
{
    this->m_size = newSize;
}
