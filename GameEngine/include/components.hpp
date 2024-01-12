/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

#include "SFML/Graphics/Texture.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <utility>

#include <cstddef>

/********-Position Component-******/
class Position
{
public:
    Position() = default;
    Position(std::pair<int, int> originPos);
    ~Position() = default;
    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int> newPos);

private:
    std::pair<int, int> m_pos;
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

/********-Score Component-******/
class ScorePoint
{
public:
    ScorePoint() = default;
    ScorePoint(int score);
    ~ScorePoint() = default;

    int getScorePoint() const;
    void setScorePoint(int score);

private:
    float m_score;
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

    operator std::size_t() const
    {
        return m_id;
    }

private:
    std::size_t m_id;
};


/********-Speed Component-******/
class Speed
{
public:
    Speed() = default;
    Speed(float speed);
    ~Speed() = default;

    float getSpeed() const;

    void setSpeed(float newSpeed);

private:
    float m_speed;
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
    Size(std::pair<float, float> originSize);
    ~Size() = default;
    std::pair<float, float> getSize() const;
    void setSize(std::pair<float, float> newSize);

private:
    std::pair<float, float> m_size;
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

enum EntityType
{
    Player,
    Other_Player,
    Enemy,
    Player_Projectile,
    Enemy_Projectile,
    Wall,
    HUD,
    Arrow_Player,
    Unknow
};

class Type
{
public:
    Type() = default;
    Type(EntityType entityType);
    ~Type() = default;

    EntityType getEntityType() const;

    void setEntityType(EntityType entityType);

    friend std::ostream& operator<<(std::ostream& os, const Type& type);

private:
    EntityType m_entityType;
};

inline std::ostream& operator<<(std::ostream& os, const Type& type)
{
    switch (type.m_entityType) {
        case EntityType::Player:
            os << "Player";
            break;
        case EntityType::Enemy:
            os << "Enemy";
            break;
        case EntityType::Player_Projectile:
            os << "Player_Projectile";
            break;
        case EntityType::Enemy_Projectile:
            os << "Enemy_Projectile";
            break;
        case EntityType::Wall:
            os << "Wall";
            break;
        case EntityType::HUD:
            os << "HUD";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

/********-Renderer Component-******/

class Renderer
{
public:
    Renderer() = default;
    explicit Renderer(const std::string& texturePath);
    ~Renderer() = default;

    sf::Sprite& getRenderer();
    sf::Texture getTexture() const;

    void setRenderer(const std::string& texturePath);

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};
