/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** network
*/
#include "Systems.hpp"

std::map<std::string, COMMAND> commandMap =
    {{"EMPTY", EMPTY},
     {"DELETE", DELETE_ENTITY},
     {"LOGIN", LOGIN},
     {"UP", UP},
     {"DOWN", DOWN},
     {"LEFT", LEFT},
     {"RIGHT", RIGHT},
     {"NEW_PLAYER", NEW_PLAYER},
     {"NEW_ENEMY", NEW_ENEMY},
     {"NEW_BOSS", NEW_BOSS},
     {"ALIVE", ALIVE},
     {"PLAYER_PROJECTILE", PLAYER_PROJECTILE},
     {"HUHUHU_PROJECTILE", HUHUHU},
     {"PLAY_BOOM_ENEMIES", PLAY_BOOM_ENEMIES},
     {"NEW_POS", NEW_POS},
     {"NEW_HEALTH", NEW_HEALTH},
     {"UPDATE", UPDATE},
     {"SHOOT", SHOOT},
     {"HUHUHU", HUHUHU},
     {"DAMAGE_TO_PLAYER", DAMAGE_TO_PLAYER},
     {"REFRESH", REFRESH},
     {"SCORE", SCORE},
     {"NEW_HUD", NEW_HUD},
     {"LEVEL", LEVEL},
     {"ARROW_PLAYER", ARROW_PLAYER},
     {"LOGIN_OK", LOGIN_OK},
     {"UNKNOWN", UNKNOWN}};

std::map<std::string, EntityType> typeMap =
    {{"Player", Player},
     {"Other_Player", Other_Player},
     {"Player_Projectile", Player_Projectile},
     {"Enemy_Projectile", Enemy_Projectile},
     {"Enemy", Enemy},
     {"HUD", HUD},
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
