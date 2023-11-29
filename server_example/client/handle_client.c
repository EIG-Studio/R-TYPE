/*
** EPITECH PROJECT, 2023
** HANDLE_CLIENT_INPUT
** File description:
** handle_client_input
*/
#include "client_funct.h"
#include "server.h"
#include "client_in.h"

static void get_cmds(client_info_t *c_info, char *cmd, fd_set *write_fds)
{
    c_info->cmd = strcat(c_info->cmd, cmd);
    for (int idx = 0; c_info->cmd != NULL && c_info->cmd[idx] != '\0'; idx++) {
        if (c_info->cmd[idx] == '\n') {
            c_info->write = true;
            FD_SET(c_info->client_socket, write_fds);
            break;
        }
    }
}

client_info_t *getclient(int client_socket, server_info_t *s_info)
{
    if (client_socket == s_info->clients[0]->client_socket)
        return s_info->clients[0];
    else
        return s_info->clients[1];
}

void handle_client_io(int client_socket, server_info_t *s_info,
    fd_set *write_fds)
{
    char *buf = malloc(sizeof(char) * BUFFER_SIZE);
    size_t n = 0;
    client_info_t *c_info = getclient(client_socket, s_info);

    memset(buf, 0, BUFFER_SIZE);
    while ((n = read(c_info->client_socket, buf, BUFFER_SIZE)) > 0) {
        buf[n] = '\0';
        get_cmds(c_info, buf, write_fds);
        if (n < BUFFER_SIZE)
            break;
    }
    free(buf);
}
