/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#include "components.hpp"

Position::Position() {
    this->m_x = 0;
    this->m_y = 0;
}

float Position::getPositionX() const {
    return this->m_x;
};

float Position::getPositionY() const {
    return this->m_y;
};

void Position::setPositionX(float mX) {
    this->m_x = mX;
};

void Position::setPositionY(float mY) {
    this->m_y = mY;
};
