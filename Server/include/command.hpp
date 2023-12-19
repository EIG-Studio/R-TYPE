/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/

#pragma once
#include "server.hpp"

#include <functional>
#include <iostream>
#include <unordered_map>

class FunctionPointer
{
public:
    FunctionPointer() = default;
    ~FunctionPointer() = default;
    void executeCommand(const std::string& command);
    static void handlePositionUpdate();

private:
    std::unordered_map<std::string, std::function<void()>> m_commands{
        {"POS", [&]() { FunctionPointer::handlePositionUpdate(); }}};
};
