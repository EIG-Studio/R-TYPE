/*
** EPITECH PROJECT, 2023
** LOOP_SERVER
** File description:
** loop_server
*/

#include "server.h"
#include "client.h"
#include "game_manage.h"

static void handle_clients(server_info_t *s_info, fd_set *read_fds,
    fd_set *write_fds, struct timeval *startTime)
{
    int result = 0;
    if (s_info->finished)
        return;
    for (int fd = 0; fd < FD_SETSIZE; fd++) {
        if (FD_ISSET(fd, read_fds)) {
            result = handle_socket(s_info, read_fds, write_fds, fd);
        }
        if (FD_ISSET(fd, write_fds))
            write_cmds(s_info, fd);
        if (result == 84) {
                break;
        }
    }
    if (s_info->started) {
        game_tick(s_info, write_fds, startTime);
    }
}

static void init_set_fds(fd_set *read_fds, fd_set *write_fds,
    server_info_t *s_info, int *max_size)
{
    FD_ZERO(read_fds);
    FD_SET(s_info->server_socket, read_fds);
    FD_SET(s_info->server_socket, write_fds);
    if (s_info->clients[0]->client_socket != 0) {
        if (!s_info->clients[0]->write)
            FD_SET(s_info->clients[0]->client_socket, read_fds);
        if (s_info->clients[0]->write)
            FD_SET(s_info->clients[0]->client_socket, write_fds);
    }
    if (s_info->clients[1]->client_socket != 0) {
        if (!s_info->clients[1]->write)
            FD_SET(s_info->clients[1]->client_socket, read_fds);
        if (s_info->clients[1]->write)
            FD_SET(s_info->clients[1]->client_socket, write_fds);
    }
    *max_size = s_info->server_socket;
    if (*max_size < s_info->clients[0]->client_socket)
        *max_size = s_info->clients[0]->client_socket;
    if (*max_size < s_info->clients[1]->client_socket)
        *max_size = s_info->clients[1]->client_socket;
}

int server_loop(server_info_t *s_info)
{
    fd_set read_fds;
    fd_set write_fds;
    int max_size = 0;
    struct timeval startTime;

    gettimeofday(&startTime, NULL);
    while (1) {
        FD_ZERO(&write_fds);
        struct timeval time;
        time.tv_sec = 0;
        time.tv_usec = TIMEOUT;
        init_set_fds(&read_fds, &write_fds, s_info, &max_size);
        if (!s_info->finished && (select(max_size + 1, &read_fds, &write_fds,
            NULL, &time)) < 0) {
            perror("select\n");
            return 84;
        }
        handle_clients(s_info, &read_fds, &write_fds, &startTime);
    }
    return 0;
}
