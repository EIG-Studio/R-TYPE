/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

#include <utility>

#include <cstddef>

/********-Position Component-******/
class Position
{
public:
    Position() = default;
    Position(std::pair<float, float> originPos);
    ~Position() = default;
    std::pair<float, float> getPosition() const;
    void setPosition(std::pair<float, float> newPos);

private:
    std::pair<float, float> m_pos;
};

/********-HealthPoint Component-******/
class HealthPoint
{
public:
    HealthPoint() = default;
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
    std::pair<float, float> getVelocity() const;
    void setVelocity(float x, float y);

private:
    std::pair<float, float> m_velo;
};

/********-ID Component-******/
class ID
{
public:
    ID() = default;
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
    Speed() = default;
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
    Damage() = default;
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
    Size() = default;
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
    HitBox() = default;
    HitBox(std::pair<float, float> originPos, std::pair<float, float> size);
    ~HitBox() = default;

    std::pair<float, float> getOriPos() const;
    std::pair<float, float> getSize() const;

    void setHitBoxPosition(std::pair<float, float> originPos, std::pair<float, float> size);

private:
    std::pair<float, float> m_originPos;
    std::pair<float, float> m_size;
};

/********-Gravity Component-******/
class Gravity
{
public:
    Gravity() = default;
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
    Shooter() = default;
    Shooter(bool isShooting);
    ~Shooter() = default;

    bool isShooting() const;

    void setIsShooting(bool isShooting);

private:
    bool m_isShooting;
};

/********-Type Component-******/

enum class EntityType {
    Player,
    Enemy,
    Player_Projectile,
    Enemy_Projectile,
    Wall,
};

class Type
{
public:
    Type() = default;
    Type(EntityType entityType);
    ~Type() = default;

    EntityType getEntityType() const;

    void setEntityType(EntityType entityType);

private:
    EntityType m_entityType;
};
