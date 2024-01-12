/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** Score
*/

#include "components.hpp"

ScorePoint::ScorePoint(int score)
{
    this->m_score = score;
}

int ScorePoint::getScorePoint() const
{
    return this->m_score;
}

void ScorePoint::setScorePoint(int score)
{
    this->m_score = score;
}
