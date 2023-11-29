/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#pragma once
#include <iostream>

class CommandsToServer
{
private:
    /* data */
public:
    CommandsToServer() = default;
    ~CommandsToServer() = default;

    int sendToServer(std::string messageToSend);
};

