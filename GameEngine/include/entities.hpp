/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"

#include <any>
#include <vector>

class Entities
{
public:
    Entities()  = default;
    ~Entities() = default;
    std::vector<std::any> components;

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
    Life     m_life;
};

/********-Enemy Entity-******/
class Enemy
{
public:
    Enemy()  = default;
    ~Enemy() = default;

private:
    Position m_position;
    Life     m_life;
};
