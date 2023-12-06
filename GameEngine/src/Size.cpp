/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** Size
*/

#include "components.hpp"

Size::Size(float size)
{
    this->_Size = size;
}

float Size::getSize() const
{
    return this->_Size;
}

void Size::setSize(int newSize)
{
    this->_Size = newSize;
}
