/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"
#include <vector>
#include <any>

class Entities
{
public:
    Entities()  = default;
    ~Entities() = default;
    std::vector<std::any> Components;

private:
};

/********-Player Entity-******/
class Player
{
public:
    Player()  = default;
    ~Player() = default;

private:
    Position m_position;
    Life m_life;
};

/********-Enemy Entity-******/
class Enemy
{
public:
    Enemy() = default;
    ~Enemy() = default;

private:
    Position m_position;
    Life m_life;
};
