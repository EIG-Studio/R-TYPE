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
    Position(std::pair<int, int> originPos);
    ~Position() = default;

    std::pair<int, int> getPosition() const;

    void setPosition(std::pair<int, int> newPos);

private:
    std::pair<int, int> _pos;
};

/********-HealthPoint Component-******/
class HealthPoint
{
public:
    HealthPoint(float hp);
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

    void setSpeed(int newSpeed);

private:
    int _Speed;
};

/********-Damage Component-******/
class Damage
{
public:
    Damage(float damage);
    ~Damage() = default;

    float getDamage() const;

    void setDamage(int newDamage);

private:
    float _Damage;
};

/********-Size Component-******/
class Size
{
public:
    Size(float size);
    ~Size() = default;

    float getSize() const;

    void setSize(int newSize);

private:
    float _Size;
};

/********-HitBox Component-******/
class HitBox
{
public:
    HitBox(std::pair<int, int> originPos, std::pair<int, int> endPos);
    ~HitBox() = default;

    std::pair<int, int> getOriginHitBoxPosition() const;
    std::pair<int, int> getEndHitBoxPosition() const;

    void setHitBoxPosition(std::pair<int, int> originPos, std::pair<int, int> endPos);

private:
    std::pair<int, int> _originPos;
    std::pair<int, int> _endPos;
};

/********-Gravity Component-******/
class Gravity
{
public:
    Gravity(float gravity, bool isGravity);
    ~Gravity() = default;

    float getGravity() const;
    bool isGravity() const;

    void setGravity(float newGravity);
    void setIsGravity(bool isGravity);

private:
    bool _isGravity;
    float _Gravity;
};

/********-Shooter Component-******/
class Shooter
{
public:
    Shooter(bool isShooting);
    ~Shooter() = default;

    bool isShooter() const;

    void setIsShooting(bool isShooting);

private:
    bool _isShooting;
};
