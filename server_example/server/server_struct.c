/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** server_struct
*/

#include "server.h"

static void init_serv_struct(server_info_t *s_info)
{
    s_info->server_socket = 0;
    s_info->started = false;
    s_info->finished = false;
    s_info->winner = -1;
}

server_info_t *init_serv(server_info_t *s_info, char *const *opt)
{
    char **list_opt;

    if (opt == NULL || (list_opt = get_opt(opt)) == NULL)
        return NULL;
    s_info->server_port = atoi(list_opt[0]);
    if (s_info->server_port > 65536 || s_info->server_port < 1000)
        return NULL;
    s_info->gravity = atof(list_opt[1]);
    s_info->info_map = get_map(list_opt[2]);
    if (!s_info->info_map)
        return NULL;
    init_serv_struct(s_info);
    s_info->clients = init_client_struct(s_info);
    if (!s_info->clients)
        return NULL;
    for (int idx = 0; list_opt[idx] != NULL; idx++)
        free(list_opt[idx]);
    free(list_opt);
    return s_info;
}

void free_struct(server_info_t *s_info)
{
    free(s_info->info_map->cells);
    free(s_info->info_map);
    close(s_info->clients[0]->client_socket);
    free(s_info->clients[0]->cmd);
    free(s_info->clients[0]);
    close(s_info->clients[1]->client_socket);
    free(s_info->clients[1]->cmd);
    free(s_info->clients[1]);
    free(s_info->clients);
    free(s_info);
}
