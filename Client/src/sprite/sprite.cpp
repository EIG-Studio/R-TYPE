/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#include "sprite/sprite.hpp"

#include <utility>

Sprite::Sprite()
{
    this->m_pathLogo = "../Client/assets/MainMenu/samuraiLogo.png";
    this->m_pathTitle = "../Client/assets/MainMenu/samuraiTitle.png";
    this->m_pathFont = "../Client/assets/Fonts/retro.ttf";
    this->m_pathCursor = "../Client/assets/Cursor/cursor_64.png";

    this->m_pathBack = "../Client/assets/Background/city_1/1.png";
    this->m_pathVeryBackBuild = "../Client/assets/Background/city_1/2.png";
    this->m_pathBackBuild = "../Client/assets/Background/city_1/3.png";
    this->m_pathMidBuild = "../Client/assets/Background/city_1/4.png";
    this->m_pathFrontBuild = "../Client/assets/Background/city_1/5.png";

    this->m_pathPlayer = "../Client/assets/Cars/189_neutral.png";
    this->m_pathEnemy = "../Client/assets/Cars/cars/190.png";
    this->m_pathBoss = "../Client/assets/Boss/v-police.png";

    this->m_pathMainSong = "../Client/assets/Songs/SAMURAI_Never-Fade-Away_instru.wav";
    this->m_pathShootSound = "../Client/assets/Songs/shoot.wav";
    this->m_pathBoomEnemies = "../Client/assets/Songs/enemiesBoom.wav";
    this->m_pathKillPlayer = "../Client/assets/Songs/death.wav";
    this->easterEgg = false;
}

//     setter     //
void Sprite::setLogoPath(std::string mString)
{
    this->m_pathLogo = std::move(mString);
}

void Sprite::setTitlePath(std::string mString)
{
    this->m_pathTitle = std::move(mString);
}

void Sprite::setMainSongPath(std::string mString)
{
    this->m_pathMainSong = std::move(mString);
}

void Sprite::setPlayerPath(std::string mString)
{
    this->m_pathPlayer = std::move(mString);
}

void Sprite::setEnemyPath(std::string mString)
{
    this->m_pathEnemy = std::move(mString);
}

void Sprite::setBossPath(std::string mString)
{
    this->m_pathBoss = std::move(mString);
}

void Sprite::setBackPath(std::string mString)
{
    this->m_pathBack = std::move(mString);
}

void Sprite::setVeryBackBuildPath(std::string mString)
{
    this->m_pathVeryBackBuild = std::move(mString);
}

void Sprite::setBackBuildPath(std::string mString)
{
    this->m_pathBackBuild = std::move(mString);
}

void Sprite::setMidBuildPath(std::string mString)
{
    this->m_pathMidBuild = std::move(mString);
}

void Sprite::setFrontBuildPath(std::string mString)
{
    this->m_pathFrontBuild = std::move(mString);
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

std::string Sprite::getCursorPath()
{
    return this->m_pathCursor;
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

std::string Sprite::getPlayerPath()
{
    return this->m_pathPlayer;
}

std::string Sprite::getEnemyPath()
{
    return this->m_pathEnemy;
}

std::string Sprite::getMainSongPath()
{
    return this->m_pathMainSong;
}

std::string Sprite::getShootSoundPath()
{
    return this->m_pathShootSound;
}

std::string Sprite::getBoomEnemiesPath()
{
    return this->m_pathBoomEnemies;
}

std::string Sprite::getBossPath()
{
    return this->m_pathBoss;
}

std::string Sprite::getKillPlayerPath()
{
    return this->m_pathKillPlayer;
}
