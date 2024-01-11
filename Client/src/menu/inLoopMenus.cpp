/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#include "menu/inLoopMenus.hpp"

#include "SFML/Window/Event.hpp"
#include "menu/menus.hpp"

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
    ChoiceMenu& choiceMenu,
    ButtonManager &buttonManager,
    HostOrJoinMenu& hostOrJoinMenu,
    SettingMenu& settingMenu)
{
    choiceMenu.setCursorPosition(windowManager.getWindow());
    buttonManager.getPlayButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    buttonManager.getSettingsButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    buttonManager.getExitButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    if (buttonManager.getPlayButton().checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY()) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        hostOrJoinMenu.onHostOrJoin = true;
        hostOrJoinMenu.setInputTextFromString("127.0.0.1");
        choiceMenu.onChoice = false;
    }
    if (buttonManager.getSettingsButton().checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
        settingMenu.onSetting = true;
        choiceMenu.onChoice = false;
    }
    if (buttonManager.getExitButton().checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
        exit(0);
    }
    buttonManager.getPlayButton().draw(windowManager.getWindow());
    buttonManager.getSettingsButton().draw(windowManager.getWindow());
    buttonManager.getExitButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(choiceMenu);
}

void InLoopMenus::settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton)
{
    retourButton.checkHover(settingMenu.getCursorPosX(), settingMenu.getCursorPosY());
    settingMenu.setCursorPosition(windowManager.getWindow());
    if (retourButton.checkClick(settingMenu.getCursorPosX(), settingMenu.getCursorPosY())) {
        settingMenu.onSetting = false;
        choiceMenu.onChoice = true;
    }
    retourButton.draw(windowManager.getWindow());
    windowManager.getWindow().draw(settingMenu);
}

void InLoopMenus::hostOrJoinMenuInLoop(
    HostOrJoinMenu& hostOrJoinMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    LobbyMenu& lobbyMenu,
    Game& game,
    CommandsToServer& commandsToServer,
    Button& retourButton,
    Button& hostButton,
    Button& joinButton,
    sf::Event& event,
    IpAdress& ipAdress)
{
    hostOrJoinMenu.setCursorPosition(windowManager.getWindow());
    retourButton.checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    hostButton.checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    joinButton.checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    if (hostButton.checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        lobbyMenu.onLobby = true;
    }
    if (joinButton.checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        game.onGame = true;
        commandsToServer.sendToServerAsync("LOGIN", ipAdress);
    }
    if (retourButton.checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        choiceMenu.onChoice = true;
        hostOrJoinMenu.setInputTextFromString("");
    }
    hostOrJoinMenu.inputText(event, ipAdress);
    windowManager.getWindow().draw(hostOrJoinMenu.getInputText());
    hostButton.draw(windowManager.getWindow());
    joinButton.draw(windowManager.getWindow());
    retourButton.draw(windowManager.getWindow());
    windowManager.getWindow().draw(hostOrJoinMenu);
}

void InLoopMenus::lobbyMenuInLoop(
    LobbyMenu& lobbyMenu,
    WindowManager& windowManager,
    HostOrJoinMenu& hostOrJoinMenu,
    Game& game,
    CommandsToServer& commandsToServer,
    Button& retourButton,
    Button& startButton,
    IpAdress& ipAdress)
{
    lobbyMenu.setCursorPosition(windowManager.getWindow());
    startButton.checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    retourButton.checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    if (startButton.checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        lobbyMenu.onLobby = false;
        game.onGame = true;
        commandsToServer.sendToServerAsync("LOGIN", ipAdress);
    }
    if (retourButton.checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        lobbyMenu.onLobby = false;
        hostOrJoinMenu.onHostOrJoin = true;
        
            
    }
    startButton.draw(windowManager.getWindow());
    retourButton.draw(windowManager.getWindow());
    windowManager.getWindow().draw(lobbyMenu.getIpAdress());
    windowManager.getWindow().draw(lobbyMenu);
}
