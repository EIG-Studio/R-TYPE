/*
** EPITECH PROJECT, 2023
** HANDLE_CLIENT_CMD
** File description:
** handle_client_cmd
*/

#include "client.h"
#include "client_funct.h"
#include "server.h"

void handle_client_id(client_info_t *c_info, server_info_t *s_info, char *buf)
{
    (void) s_info;
    (void) buf;
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "ID %d\n", c_info->id);
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
}

void handle_client_map(client_info_t *c_info, server_info_t *s_info, char *buf)
{
    (void) buf;
    if (!s_info || !c_info)
        return;
    float gravity = s_info->gravity;
    int width = s_info->info_map->width;
    int height = s_info->info_map->height;
    char *cells = s_info->info_map->cells;
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "MAP %f %d %d %s\n", gravity,
        width, height, cells);
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
}

void handle_client_ready(client_info_t *c_info, server_info_t *s_info,
    char *buf)
{
    (void) s_info;
    (void) buf;
    if (!c_info)
        return;
    c_info->ready = true;
    if (s_info->clients[0]->ready && s_info->clients[1]->ready
        && !s_info->started) {
        handle_client_start(c_info);
        handle_client_start(s_info->clients[0]);
        s_info->started = true;
        handle_client_player(s_info->clients[0], s_info->clients[0]);
        handle_client_player(s_info->clients[0], s_info->clients[1]);
        handle_client_player(s_info->clients[1], s_info->clients[0]);
        handle_client_player(s_info->clients[1], s_info->clients[1]);
    }
}

void handle_client_fire(client_info_t *c_info, server_info_t *s_info, char *buf)
{
    if (!c_info || !buf || !s_info->started)
        return;
    (void) s_info;
    if (atoi(buf) == 1)
        c_info->fire_state = 1;
    if (atoi(buf) == 0)
        c_info->fire_state = 0;
}
