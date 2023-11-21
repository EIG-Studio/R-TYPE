/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#include "sprite/sprite.hpp"

Sprite::Sprite()
{
    this->m_pathLogo          = "../assets/MainMenu/samuraiLogo.png";
    this->m_pathTitle         = "../assets/MainMenu/samuraiTitle.png";
    this->m_pathFont          = "../assets/Fonts/retro.ttf";
    this->m_pathMainSong      = "../assets/Songs/SAMURAI_Never-Fade-Away_instru.wav";
    this->m_pathBack          = "../assets/Background/city_1/1.png";
    this->m_pathVeryBackBuild = "../assets/Background/city_1/2.png";
    this->m_pathBackBuild     = "../assets/Background/city_1/3.png";
    this->m_pathMidBuild      = "../assets/Background/city_1/4.png";
    this->m_pathFrontBuild    = "../assets/Background/city_1/5.png";
    this->easterEgg           = false;
}


//     setter     //
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

void Sprite::setBackPath(std::string mString)
{
    this->m_pathBack = mString;
}


//     getter     //
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

std::string Sprite::getBackPath()
{
    return this->m_pathBack;
}

std::string Sprite::getVeryBackBuildPath()
{
    return this->m_pathVeryBackBuild;
}

std::string Sprite::getBackBuildPath()
{
    return this->m_pathBackBuild;
}

std::string Sprite::getMidBuildPath()
{
    return this->m_pathMidBuild;
}

std::string Sprite::getFrontBuildPath()
{
    return this->m_pathFrontBuild;
}
