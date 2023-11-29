/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** game
*/

#include "game_manage.h"

void change_coin(server_info_t *s_info, int player, int val)
{
    if (player + 1 == 1) {
        if (s_info->info_map->cells[val] == 'p')
            s_info->info_map->cells[val] = 'z';
        else
            s_info->info_map->cells[val] = 'm';
    }
    if (player + 1 == 2) {
        if (s_info->info_map->cells[val] == 'm')
            s_info->info_map->cells[val] = 'z';
        else
            s_info->info_map->cells[val] = 'p';
    }
    s_info->clients[player]->coin += 1;
}

static void send_data_to_players(server_info_t *s_info, fd_set *write_fds,
    client_info_t *client, client_info_t *client2)
{
    if (FD_ISSET(client->client_socket, write_fds) &&
        FD_ISSET(client2->client_socket, write_fds)) {
        handle_client_player(s_info->clients[0], client);
        handle_client_player(s_info->clients[0], client2);
        handle_client_player(s_info->clients[1], client);
        handle_client_player(s_info->clients[1], client2);
        game_end(s_info);
        client->write = false;
        client2->write = false;
    } else {
        FD_SET(client->client_socket, write_fds);
        client->write = true;
        FD_SET(client2->client_socket, write_fds);
        client2->write = true;
    }
}

void game_tick(server_info_t *s_info, fd_set *write_fds,
    struct timeval *startTime)
{
    client_info_t *client = s_info->clients[0];
    client_info_t *client2 = s_info->clients[1];

    if (get_elapsed_time(startTime) == false ||
        !s_info->started || s_info->finished)
        return;
    for (int id = 0; id < 2; id++) {
        player_collision(s_info, id);
        player_movement(s_info->clients[id], s_info->gravity,
            s_info->info_map->height);
    }
    send_data_to_players(s_info, write_fds, client, client2);
}
