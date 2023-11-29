/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** client_struct
*/

#include "client.h"
#include "server.h"

static void init_client(client_info_t *client, int height, int id)
{
    client->ready = false;
    client->isdead = false;
    client->x = 0.0;
    client->y = height / 2;
    client->id = id;
    client->coin = 0;
    client->client_socket = 0;
    client->fire_state = 0;
    client->write = false;
    client->cmd = malloc(sizeof(char) * BUFFER_SIZE);
    memset(client->cmd, 0, BUFFER_SIZE);
}

void *init_client_struct(server_info_t *s_info)
{
    s_info->clients = malloc(sizeof(client_info_t*) * 2);
    if (!s_info->clients)
        return NULL;
    s_info->clients[0] = malloc(sizeof(client_info_t));
    s_info->clients[1] = malloc(sizeof(client_info_t));
    if (!s_info->clients[0] || !s_info->clients[1])
        return NULL;
    init_client(s_info->clients[0], s_info->info_map->height, 1);
    init_client(s_info->clients[1], s_info->info_map->height, 2);
    return s_info->clients;
}
