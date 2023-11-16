/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** menu
*/

#include <iostream>
#include "menu.hpp"

Menu::Menu() {
    this->menuLogoTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->menuLogoSprite.setTexture(this->menuLogoTexture);
    this->menuTitleTexture.loadFromFile(PATH_TEXTURE_MENU_TITLE);
    this->menuTitleSprite.setTexture(this->menuTitleTexture);

    //// Trouver un moyen pour rendre ça plus beau
    menuLogoSprite.setScale(260 / menuLogoSprite.getLocalBounds().width, 299 / menuLogoSprite.getLocalBounds().height);
    menuLogoSprite.setPosition(800 / 2 - 260 / 2, 50);

    menuTitleSprite.setScale(395 / menuTitleSprite.getLocalBounds().width, 53 / menuTitleSprite.getLocalBounds().height);
    menuTitleSprite.setPosition(800 / 2 - 395 / 2, 600 / 1.5 -  53 / 2);
    this->onMenu = true;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &menuLogoTexture;
    states.texture = &menuTitleTexture;
    target.draw(menuLogoSprite, states);
    target.draw(menuTitleSprite, states);
}

//sf::FloatRect Menu::getSettings() {
//    sf::FloatRect rect = this->setting_sprite.getGlobalBounds();
//    return rect;
//}

//sf::FloatRect Menu::getExit() {
//    sf::FloatRect rect = this->exit_sprite.getGlobalBounds();
//    return rect;
//}
