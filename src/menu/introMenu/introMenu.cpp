#include "menu/introMenu/introMenu.hpp"

#include "button.hpp"
#include "music/music.hpp"

#include <iostream>

Menu::Menu()
{
    this->m_menuLogoTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->m_menuLogoSprite.setTexture(this->m_menuLogoTexture);
    this->m_menuTitleTexture.loadFromFile(PATH_TEXTURE_MENU_TITLE);
    this->m_menuTitleSprite.setTexture(this->m_menuTitleTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_menuLogoSprite.setScale(260 / m_menuLogoSprite.getLocalBounds().width, 299 / m_menuLogoSprite.getLocalBounds().height);
    m_menuLogoSprite.setPosition(800 / 2 - 260 / 2, 50);

    m_menuTitleSprite.setScale(395 / m_menuTitleSprite.getLocalBounds().width,
                               53 / m_menuTitleSprite.getLocalBounds().height);
    m_menuTitleSprite.setPosition(800 / 2 - 395 / 2, 600 / 1.5 - 53 / 2);
    this->onMenu = true;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_menuLogoTexture;
    states.texture = &m_menuTitleTexture;
    target.draw(m_menuLogoSprite, states);
    target.draw(m_menuTitleSprite, states);
}

//sf::FloatRect Menu::getSettings() {
//    sf::FloatRect rect = this->setting_sprite.getGlobalBounds();
//    return rect;
//}

//sf::FloatRect Menu::getExit() {
//    sf::FloatRect rect = this->exit_sprite.getGlobalBounds();
//    return rect;
//}

ChoiceMenu::ChoiceMenu()
{
    this->logoSamuraiTexture.loadFromFile(PATH_TEXTURE_MENU_LOGO);
    this->logoSamuraiSprite.setTexture(this->logoSamuraiTexture);

    //// Trouver un moyen pour rendre ça plus beau
    logoSamuraiSprite.setScale(87 / logoSamuraiSprite.getLocalBounds().width, 100 / logoSamuraiSprite.getLocalBounds().height);
    logoSamuraiSprite.setPosition(20, 20);

    this->onChoice = false;
}

void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &logoSamuraiTexture;
    target.draw(logoSamuraiSprite, states);
}
