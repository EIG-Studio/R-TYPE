/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

#include <utility>

class IComponents
{
public:
    virtual ~IComponents() = 0;

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

/********-HealthPoint Component-******/
class HealthPoint
{
public:
    HealthPoint();
    ~HealthPoint() = default;

    float getHealthPoint() const;

    void setHealthPoint(float mLp);

private:
    float m_lp;
};

/********-HealthPoint Component-******/
class Velocity
{
public:
    Velocity();
    ~Velocity() = default;

    std::pair<int, int> getVelocity() const;

    void setVelocity(int x, int y);

private:
    std::pair<int, int> _velo;
};
