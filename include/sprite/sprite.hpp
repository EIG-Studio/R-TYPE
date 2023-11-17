/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

#include "sfml.hpp"
#include <string>

class Sprite : public sf::Transformable
{
public:
    Sprite();
    ~Sprite() override = default;

    void setLogoPath(std::string mString);

    std::string getLogoPath();
    std::string getTitlePath();
    std::string getFontPath();

private:
    std::string m_pathLogo;
    std::string m_pathTitle;
    std::string m_pathFont;

};
