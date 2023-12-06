/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ID
*/

#include "components.hpp"

ID::ID(std::size_t id)
{
    this->_ID = id;
}

std::size_t ID::getID() const
{
    return this->_ID;
}
