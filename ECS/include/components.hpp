/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

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

/********-Health Component-******/
class Health
{
public:
    Health();
    ~Health() = default;

    float getHealthPoint() const;

    void setHealthPoint(float mHp);

private:
    float m_hp;
};

/********-Damage Component-******/
class Damage
{
    public:
    Damage();
    ~Damage();

    float getDamagePoint() const;

    void setDamagePoint(float mDp);

    private:
    float m_dp;
};

/********-Id Component-******/
class Id
{
    public:
    Id();
    ~Id();

    size_t getId() const;
    void setId(size_t mId);

    private:
    size_t m_id;
};

/********-Type Component-******/
class Type
{
    public:
    Type();
    ~Type();

    enum class m_type {
        TYPE1,
        TYPE2,
        TYPE3
    };

    m_type getType() const;
    void setType(m_type newType);

    private:
    m_type currentType;
};