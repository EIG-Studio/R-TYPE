/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** game_manage
*/

#include "game_manage.h"

void player_movement(client_info_t *client, float gravity, int height)
{
    double diff;
    double velo;

    velo = gravity * TIMEOUT / 1000000;
    diff = (double)5 * TIMEOUT / 1000000;
    client->x += diff;
    if (client->fire_state == 1) {
        if (client->y + velo < height) {
            client->y += velo;
            return;
        }
    }
    if (client->fire_state == 0) {
        if (client->y - velo <= 0) {
            client->y = 0;
        } else
            client->y -= velo;
    }
}

static void player_collision_coin(server_info_t *s_info, int player)
{
    int player_x = (int)floor(s_info->clients[player]->x);
    int player_y = (s_info->info_map->height - 1) -
        (int)floor(s_info->clients[player]->y);
    int val = player_x + (s_info->info_map->width * player_y);

    handle_client_coin(s_info->clients[0], player + 1,
        player_x, player_y);
    handle_client_coin(s_info->clients[1], player + 1,
        player_x, player_y);
    change_coin(s_info, player, val);
}

void player_collision(server_info_t *s_info, int player)
{
    int player_x = (int)floor(s_info->clients[player]->x);
    int player_y = (s_info->info_map->height - 1) -
        (int)floor(s_info->clients[player]->y);
    int val = player_x + (s_info->info_map->width * player_y);

    if (s_info->info_map->cells[val] == 'c'
        || (player + 1 == 1 && s_info->info_map->cells[val] == 'p')
        || (player + 1 == 2 && s_info->info_map->cells[val] == 'm')) {
        player_collision_coin(s_info, player);
    }
    if (s_info->info_map->cells[val] == 'e') {
        s_info->clients[player]->isdead = true;
    }
}

static void game_score(server_info_t *s_info)
{
    if (s_info->clients[0]->coin > s_info->clients[1]->coin) {
        handle_client_finish(s_info->clients[0], 1);
        handle_client_finish(s_info->clients[1], 1);
    } else if (s_info->clients[0]->coin < s_info->clients[1]->coin) {
        handle_client_finish(s_info->clients[0], 2);
        handle_client_finish(s_info->clients[1], 2);
    } else {
        handle_client_finish(s_info->clients[0], -1);
        handle_client_finish(s_info->clients[1], -1);
        printf("ici\n");
    }
    s_info->finished = true;
    return;
}

void game_end(server_info_t *s_info)
{
    if (s_info->finished)
        return;
    if (s_info->clients[0]->isdead && s_info->clients[1]->isdead) {
        handle_client_finish(s_info->clients[0], -1);
        handle_client_finish(s_info->clients[1], -1);
        s_info->finished = true;
    }
    if (s_info->clients[0]->isdead && !s_info->clients[1]->isdead) {
        handle_client_finish(s_info->clients[0], 2);
        handle_client_finish(s_info->clients[1], 2);
        s_info->finished = true;
    }
    if (s_info->clients[1]->isdead && !s_info->clients[0]->isdead) {
        handle_client_finish(s_info->clients[0], 1);
        handle_client_finish(s_info->clients[1], 1);
        s_info->finished = true;
    }
    if (s_info->clients[0]->x >= s_info->info_map->width &&
        s_info->clients[1]->x >= s_info->info_map->width)
        game_score(s_info);
}
