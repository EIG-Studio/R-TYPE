/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** handle_send_client
*/

#include "client_in.h"

static unordered_map_t methodmap[] = {
    {"ID\n", &handle_client_id},
    {"MAP\n", &handle_client_map},
    {"READY\n", &handle_client_ready},
    {"FIRE", &handle_client_fire},
    {"", 0}
};

static int handle_client_buf(client_info_t *c_info, server_info_t *s_info,
    char *cmd)
{
    size_t size = 0;

    for (int idx = 0; methodmap[idx].method; idx++) {
        size = strlen(methodmap[idx].in_method);
        if (strncmp(methodmap[idx].in_method, cmd, size) == 0) {
            (methodmap[idx].method)(c_info, s_info, cmd + size);
        }
    }
    return 0;
}

char *rm_str(char *src, int n_rm)
{
    int idx = 0;

    for (int ind = 0; src[ind] != '\0'; ind++) {
        if (ind >= n_rm) {
            src[idx] = src[ind];
            idx++;
        }
    }
    src[idx] = '\0';
    return src;
}

static void send_cmds(client_info_t *c_info, server_info_t *s_info)
{
    for (int idx = 0; c_info->cmd != NULL && c_info->cmd[idx] != '\0'; idx++) {
        if (c_info->cmd[idx] == '\n') {
            handle_client_buf(c_info, s_info, c_info->cmd);
            c_info->cmd = rm_str(c_info->cmd, idx + 1);
        }
    }
}

int write_cmds(server_info_t *s_info, int socket)
{
    client_info_t *c_info = getclient(socket, s_info);

    if (c_info->cmd[0] != '\0') {
        send_cmds(c_info, s_info);
        c_info->write = false;
    }
    return 0;
}
