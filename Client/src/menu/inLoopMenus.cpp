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

void InLoopMenus::choiceMenuInLoop(
    WindowManager& windowManager,
    ChoiceMenu &choiceMenu,
    Button &playButton,
    Button &settingsButton,
    Button &exitButton,
    Game &game,
    CommandsToServer &commandsToServer,
    SettingMenu &settingMenu)
{
    choiceMenu.setCursorPosition(windowManager.getWindow());
    playButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    settingsButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    exitButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    if (playButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY()) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        game.onGame = true;
        choiceMenu.onChoice = false;
        commandsToServer.sendToServerAsync("LOGIN");
        commandsToServer.sendToServerAsync("UPDATE");
    }
    if (settingsButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
        settingMenu.onSetting = true;
        choiceMenu.onChoice = false;
    }
    if (exitButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
        exit(0);
    }
    playButton.draw();
    settingsButton.draw();
    exitButton.draw();
    windowManager.getWindow().draw(choiceMenu);
}