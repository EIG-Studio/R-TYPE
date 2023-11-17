/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#include "sprite/sprite.hpp"

Sprite::Sprite()
{
    this->m_pathLogo  = "../assets/MainMenu/samuraiLogo.png";
    this->m_pathTitle = "../assets/MainMenu/samuraiTitle.png";
    this->m_pathFont  = "../assets/Fonts/retro.ttf";
}

void Sprite::setLogoPath(std::string mString)
{
    this->m_pathLogo = mString;
}

void Sprite::setTitlePath(std::string mString)
{
    this->m_pathTitle = mString;
}


std::string Sprite::getLogoPath()
{
    return this->m_pathLogo;
}

std::string Sprite::getTitlePath()
{
    return this->m_pathTitle;
}

std::string Sprite::getFontPath()
{
    return this->m_pathFont;
}
