/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#include "menu/inGame.hpp"

Game::Game()
{
    this->m_testTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->m_testSprite.setTexture(this->m_testTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_testSprite.setScale(260 / m_testSprite.getLocalBounds().width, 299 / m_testSprite.getLocalBounds().height);
    m_testSprite.setPosition(800 / 2 - 260 / 2, 50);
    this->onGame = false;
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_testTexture;
    target.draw(m_testSprite, states);
}