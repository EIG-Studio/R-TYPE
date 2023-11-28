/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once
#include "systems.hpp"

class Components
{
public:
    Components() = default;
    ~Components() = default;

    private:
};

/********-Position Component-******/
class Position
{
public:
    Position();
    ~Position() = default;

    float getPositionX() const;
    float getPositionY() const;

    void setPositionX(float mX);
    void setPositionY(float mY);

private:
    float m_x;
    float m_y;
};

/********-Life Component-******/
class Life
{
public:
    Life();
    ~Life() = default;

    float getLifePoint() const;

    void setLifePoint(float mLp);

private:
    float m_lp;
};
