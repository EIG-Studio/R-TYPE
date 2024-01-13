/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#include "menu/inLoopMenus.hpp"

#include "SFML/Window/Event.hpp"
#include "menu/inLoopGame.hpp"
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
    ButtonManager& buttonManager,
    HostOrJoinMenu& hostOrJoinMenu,
    SettingMenu& settingMenu,
    Music& music)
{
    choiceMenu.setCursorPosition(windowManager.getWindow());
    buttonManager.getPlayButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    buttonManager.getSettingsButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    buttonManager.getExitButton().checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
    if (music.musicMenu.getStatus() == sf::SoundSource::Stopped) {
        music.musicMenu.play();
    }
    if (buttonManager.getPlayButton().checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY()) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        hostOrJoinMenu.onHostOrJoin = true;
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

void InLoopMenus::settingsMenuInLoop(
    SettingMenu& settingMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    ButtonManager& buttonManager)
{
    buttonManager.getRetourButton().checkHover(settingMenu.getCursorPosX(), settingMenu.getCursorPosY());
    settingMenu.setCursorPosition(windowManager.getWindow());
    if (buttonManager.getRetourButton().checkClick(settingMenu.getCursorPosX(), settingMenu.getCursorPosY())) {
        settingMenu.onSetting = false;
        choiceMenu.onChoice = true;
    }
    buttonManager.getRetourButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(settingMenu);
}

void InLoopMenus::hostOrJoinMenuInLoop(
    HostOrJoinMenu& hostOrJoinMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    LobbyMenu& lobbyMenu,
    Game& game,
    CommandsToServer& commandsToServer,
    ButtonManager& buttonManager,
    sf::Event& event,
    IpAdress& ipAdress)
{
    hostOrJoinMenu.setCursorPosition(windowManager.getWindow());
    buttonManager.getRetourButton().checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    buttonManager.getHostButton().checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    buttonManager.getJoinButton().checkHover(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY());
    buttonManager.getIpButton().setText(hostOrJoinMenu.getInputText().getString());
    buttonManager.getIpButton().setPosition(sf::Vector2f(
        windowManager.getWindow().getSize().x / 2 - hostOrJoinMenu.getInputText().getString().getSize() * 20 / 2,
        windowManager.getWindow().getSize().y / 2));
    buttonManager.getIpButton().setSize(sf::Vector2f(hostOrJoinMenu.getInputText().getString().getSize() * 20, 50));
    if (buttonManager.getHostButton().checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        lobbyMenu.onLobby = true;
    }
    if (buttonManager.getJoinButton().checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        game.onGame = true;
        commandsToServer.sendToServerAsync("LOGIN", ipAdress);
    }
    if (buttonManager.getRetourButton().checkClick(hostOrJoinMenu.getCursorPosX(), hostOrJoinMenu.getCursorPosY())) {
        hostOrJoinMenu.onHostOrJoin = false;
        choiceMenu.onChoice = true;
        hostOrJoinMenu.setInputTextFromString("");
    }
    hostOrJoinMenu.inputText(event, ipAdress);
    windowManager.getWindow().draw(hostOrJoinMenu.getInputText());
    buttonManager.getHostButton().draw(windowManager.getWindow());
    buttonManager.getJoinButton().draw(windowManager.getWindow());
    buttonManager.getRetourButton().draw(windowManager.getWindow());
    buttonManager.getIpButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(hostOrJoinMenu);
}

void levelOneConfig(Game& game, Sprite& sprite)
{
    sprite.setBackPath("../Client/assets/Background/city_1/1.png");
    sprite.setVeryBackBuildPath("../Client/assets/Background/city_1/2.png");
    sprite.setBackBuildPath("../Client/assets/Background/city_1/3.png");
    sprite.setMidBuildPath("../Client/assets/Background/city_1/4.png");
    sprite.setFrontBuildPath("../Client/assets/Background/city_1/5.png");
    game.setPath(sprite);
    game.current_level = 1;
}

void levelTwoConfig(Game& game, Sprite& sprite)
{
    sprite.setBackPath("../Client/assets/Background/city_7/1.png");
    sprite.setVeryBackBuildPath("../Client/assets/Background/city_7/2.png");
    sprite.setBackBuildPath("../Client/assets/Background/city_7/3.png");
    sprite.setMidBuildPath("../Client/assets/Background/city_7/4.png");
    sprite.setFrontBuildPath("../Client/assets/Background/city_7/5.png");
    game.setPath(sprite);
    game.current_level = 2;
}

void InLoopMenus::lobbyMenuInLoop(
    LobbyMenu& lobbyMenu,
    WindowManager& windowManager,
    HostOrJoinMenu& hostOrJoinMenu,
    Game& game,
    Sprite& sprite,
    CommandsToServer& commandsToServer,
    ButtonManager& buttonManager,
    IpAdress& ipAdress)
{
    lobbyMenu.setCursorPosition(windowManager.getWindow());
    //buttonManager.getLevelOneButton().checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    //buttonManager.getLevelTwoButton().checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    buttonManager.getStartButton().checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    buttonManager.getRetourButton().checkHover(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY());
    if (buttonManager.getStartButton().checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        lobbyMenu.onLobby = false;
        game.onGame = true;
        commandsToServer.sendToServerAsync("LOGIN", ipAdress);
    }
    if (buttonManager.getRetourButton().checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        lobbyMenu.onLobby = false;
        hostOrJoinMenu.onHostOrJoin = true;
    }
    if (buttonManager.getLevelOneButton().checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        buttonManager.getLevelOneButton().setOutlineColor(sf::Color::Red);
        if (buttonManager.getLevelTwoButton().getOutlineColor() == sf::Color::Red)
            buttonManager.getLevelTwoButton().setOutlineColor(sf::Color::White);
        levelOneConfig(game, sprite);
        commandsToServer.sendToServerAsync("LEVEL 1", ipAdress);
    }
    if (buttonManager.getLevelTwoButton().checkClick(lobbyMenu.getCursorPosX(), lobbyMenu.getCursorPosY())) {
        buttonManager.getLevelTwoButton().setOutlineColor(sf::Color::Red);
        if (buttonManager.getLevelOneButton().getOutlineColor() == sf::Color::Red)
            buttonManager.getLevelOneButton().setOutlineColor(sf::Color::White);
        levelTwoConfig(game, sprite);
        commandsToServer.sendToServerAsync("LEVEL 2", ipAdress);
    }
    buttonManager.getLevelOneButton().draw(windowManager.getWindow());
    buttonManager.getLevelTwoButton().draw(windowManager.getWindow());
    buttonManager.getStartButton().draw(windowManager.getWindow());
    buttonManager.getRetourButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(lobbyMenu.getIpAdress());
    windowManager.getWindow().draw(lobbyMenu);
}

void InLoopMenus::youWinMenuInLoop(YouWinMenu& youWinMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, ButtonManager& buttonManager)
{
    buttonManager.getRetourButton().checkHover(youWinMenu.getCursorPosX(), youWinMenu.getCursorPosY());
    youWinMenu.setCursorPosition(windowManager.getWindow());
    if (buttonManager.getRetourButton().checkClick(youWinMenu.getCursorPosX(), youWinMenu.getCursorPosY())) {
        youWinMenu.onWin = false;
        choiceMenu.onChoice = true;
    }
    buttonManager.getRetourButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(youWinMenu);
}

void InLoopMenus::youLooseMenuInLoop(
    YouLooseMenu& youLooseMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    ButtonManager& buttonManager)
{
    buttonManager.getRetourButton().checkHover(youLooseMenu.getCursorPosX(), youLooseMenu.getCursorPosY());
    youLooseMenu.setCursorPosition(windowManager.getWindow());
    if (buttonManager.getRetourButton().checkClick(youLooseMenu.getCursorPosX(), youLooseMenu.getCursorPosY())) {
        youLooseMenu.onLoose = false;
        choiceMenu.onChoice = true;
    }
    buttonManager.getRetourButton().draw(windowManager.getWindow());
    windowManager.getWindow().draw(youLooseMenu);
}

void menuChoice(
    Menu& menu,
    InLoopMenus& introMenu,
    WindowManager& windowManager,
    Music& music,
    sf::Clock& clock,
    ChoiceMenu& choiceMenu,
    HostOrJoinMenu& hostOrJoinMenu,
    LobbyMenu& lobbyMenu,
    ButtonManager& buttonManager,
    Game& game,
    CommandsToServer& commandsToServer,
    SettingMenu& settingMenu,
    InLoopGame& inLoopGame,
    YouWinMenu& youWinMenu,
    YouLooseMenu& youLooseMenu,
    sf::Event& event,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    IpAdress& ipAdress)
{
    if (menu.onMenu) {
        introMenu.introMenuInLoop(menu, windowManager, music, clock);
    } else if (choiceMenu.onChoice) {
        introMenu.choiceMenuInLoop(windowManager, choiceMenu, buttonManager, hostOrJoinMenu, settingMenu, music);
    } else if (hostOrJoinMenu.onHostOrJoin) {
        introMenu.hostOrJoinMenuInLoop(hostOrJoinMenu, windowManager, choiceMenu, lobbyMenu, game, commandsToServer, buttonManager, event, ipAdress);
    } else if (lobbyMenu.onLobby) {
        introMenu.lobbyMenuInLoop(lobbyMenu, windowManager, hostOrJoinMenu, game, sprite, commandsToServer, buttonManager, ipAdress);
    } else if (settingMenu.onSetting) {
        introMenu.settingsMenuInLoop(settingMenu, windowManager, choiceMenu, buttonManager);
    } else if (game.onGame) {
        inLoopGame
            .gameInLoop(event, windowManager, game, music, commandsToServer, sprite, onGameClock, registry, buttonManager, choiceMenu, youWinMenu, youLooseMenu, ipAdress);
    } else if (youWinMenu.onWin) {
        introMenu.youWinMenuInLoop(youWinMenu, windowManager, choiceMenu, buttonManager);
    } else if (youLooseMenu.onLoose) {
        introMenu.youLooseMenuInLoop(youLooseMenu, windowManager, choiceMenu, buttonManager);
    }
}
