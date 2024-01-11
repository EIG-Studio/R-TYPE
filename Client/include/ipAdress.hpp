/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** ipAdress
*/

#pragma once

#include <iostream>
#include <utility>

class IpAdress
{
public:
    IpAdress()
    {
        m_userInput = "127.0.0.1";
    };
    ~IpAdress() = default;
    std::string getUserInput()
    {
        return m_userInput;
    };
    void setUserInput(std::string mString)
    {
        m_userInput = std::move(mString);
    }

private:
    std::string m_userInput;
};
