/*
** EPITECH PROJECT, 2023
** HANDLE_CLIENT_CMD
** File description:
** handle_client_cmd
*/

#include "client.h"
#include "server.h"

void handle_client_player(client_info_t *c_info, client_info_t *send_info)
{
    int id = send_info->id;
    double x = send_info->x;
    double y = send_info->y;
    int score = send_info->coin;
    int firestate = send_info->fire_state;
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "PLAYER %d %f %f %d %d\n",
        id, x, y, score, firestate);
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
    return;
}

void handle_client_coin(client_info_t *c_info, int id, int x, int y)
{
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "COIN %d %d %d\n", id, x, y);
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
    return;
}

void handle_client_finish(client_info_t *c_info, int winner)
{
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "FINISH %d\n", winner);
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
    return;
}

void handle_client_start(client_info_t *c_info)
{
    char *str = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n;

    sprintf(str, "START\n");
    while ((n = write(c_info->client_socket, str, strlen(str))) > 0) {
        if (n >= strlen(str))
            break;
        str = rm_str(str, n);
    }
    free(str);
    return;
}
