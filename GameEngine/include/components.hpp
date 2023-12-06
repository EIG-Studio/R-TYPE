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
struct Position {
    float x, y;
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
struct Velocity {
    float dx, dy;
};

/********-ID Component-******/
class ID
{
public:
    ID(std::size_t id);
    ~ID() = default;

    std::size_t getID() const;

private:
    std::size_t m_id;
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
    int m_speed;
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
    float m_damage;
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
    float m_size;
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
    std::pair<int, int> m_originPos;
    std::pair<int, int> m_endPos;
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
    bool m_isGravity;
    float m_gravity;
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
    bool m_isShooting;
};
