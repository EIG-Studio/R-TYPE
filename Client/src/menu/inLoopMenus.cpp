/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#include "menu/inLoopMenus.hpp"

void InLoopMenus::introMenuInLoop(Menu& menu, WindowManager& windowManager, Music& music, sf::Clock& clock)
{
    if (music.playMenuMusic) {
        music.musicMenu.play();
        music.playMenuMusic = false;
    }
    sf::Time elapsed = clock.getElapsedTime();
    clock = menu.blinkingText(clock, elapsed);
    windowManager.getWindow().draw(menu);
}

void InLoopMenus::settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton)
{
    retourButton.checkHover(settingMenu.getCursorPosX(), settingMenu.getCursorPosY());
    settingMenu.setCursorPosition(windowManager.getWindow());
    if (retourButton.checkClick(settingMenu.getCursorPosX(), settingMenu.getCursorPosY())) {
        settingMenu.onSetting = false;
        choiceMenu.onChoice = true;
    }
    retourButton.draw();
    windowManager.getWindow().draw(settingMenu);
}
