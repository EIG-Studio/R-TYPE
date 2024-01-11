/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** network
*/
#include "Systems.hpp"

static std::map<std::string, COMMAND> commandMap =
    {{"EMPTY", EMPTY},
     {"DELETE", DELETE},
     {"LOGIN", LOGIN},
     {"UP", UP},
     {"DOWN", DOWN},
     {"LEFT", LEFT},
     {"RIGHT", RIGHT},
     {"NEW_PLAYER", NEW_PLAYER},
     {"NEW_ENNEMY", NEW_ENNEMY},
     {"ALIVE", ALIVE},
     {"PLAYER_PROJECTILE", PLAYER_PROJECTILE},
     {"PLAY_BOOM_ENNEMIES", PLAY_BOOM_ENNEMIES},
     {"NEW_POS", NEW_POS},
     {"UPDATE", UPDATE},
     {"SHOOT", SHOOT},
     {"REFRESH", REFRESH},
     {"UNKNOWN", UNKNOWN}};

static std::map<std::string, EntityType> typeMap =
    {{"Player", Player},
     {"Other_Player", Other_Player},
     {"Player_Projectile", Player_Projectile},
     {"Enemy_Projectile", Enemy_Projectile},
     {"Enemy", Enemy},
     {"Wall", Wall}};

COMMAND getCommand(const std::string& commandStr)
{
    auto it = commandMap.find(commandStr);
    if (it != commandMap.end()) {
        return it->second;
    }
    return UNKNOWN;
}

EntityType getType(const std::string& typeStr)
{
    auto it = typeMap.find(typeStr);
    if (it != typeMap.end()) {
        return it->second;
    }
    return Unknow;
}