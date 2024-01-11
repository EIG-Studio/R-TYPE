/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** Score
*/

#include "components.hpp"

ScorePoint::ScorePoint(int hp)
{
    this->m_score = hp;
}

int ScorePoint::getScorePoint() const
{
    return this->m_score;
}

void ScorePoint::setScorePoint(int score)
{
    this->m_score = score;
}