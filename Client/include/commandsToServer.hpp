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
    std::string m_newPos;

public:
    CommandsToServer()  = default;
    ~CommandsToServer() = default;

    int sendToServer(std::string msg);
    std::string getNewPos();
};
