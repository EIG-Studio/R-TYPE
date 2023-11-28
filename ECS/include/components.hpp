/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** components
*/

#pragma once

class Components
{
public:
    Components() = default;
    ~Components() = default;

    private:
};

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
