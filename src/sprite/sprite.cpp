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
    this->m_pathMainSong = "../assets/Songs/SAMURAI_Never-Fade-Away_instru.wav";
    this->easterEgg = false;
}

void Sprite::setLogoPath(std::string mString)
{
    this->m_pathLogo = mString;
}

void Sprite::setTitlePath(std::string mString)
{
    this->m_pathTitle = mString;
}

void Sprite::setMainSongPath(std::string mString)
{
    this->m_pathMainSong = mString;
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

std::string Sprite::getMainSongPath()
{
    return this->m_pathMainSong;
}
