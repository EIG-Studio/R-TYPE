/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

#include <utility>
#include <cstddef>

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

/********-Velocity Component-******/
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

/********-ID Component-******/
class ID
{
public:
    ID(std::size_t id);
    ~ID() = default;

    std::size_t getID() const;

private:
    std::size_t _ID;
};

/********-Speed Component-******/
class Speed
{
public:
    Speed(int speed);
    ~Speed() = default;

    int getSpeed() const;

    void setSpeed(int newspeed);

private:
    int _Speed;
};
