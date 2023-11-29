/*
** EPITECH PROJECT, 2023
** SERVER
** File description:
** File to manage server
*/

#include "server.h"

static void *set_socket_info(server_info_t *s_info)
{
    struct sockaddr_in socket_info;

    socket_info.sin_family = IPPROTO_IP;
    socket_info.sin_port = htons(s_info->server_port);
    socket_info.sin_addr.s_addr = INADDR_ANY;
    if (bind(s_info->server_socket,
        (struct sockaddr *)&socket_info, sizeof(socket_info)) == -1) {
        perror("ERROR: binding info on server socket !\n");
        return NULL;
    }
    if (listen(s_info->server_socket, 50) == -1) {
        perror("ERROR: listening function in server !\n");
        return NULL;
    }
    return s_info;
}

server_info_t *create_server(char *const *opt)
{
    server_info_t *s_info = malloc(sizeof(server_info_t));

    s_info = init_serv(s_info, opt);
    if (!s_info)
        return NULL;
    s_info->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (s_info->server_socket == -1) {
        perror("ERROR: can't create a socket !\n");
        return NULL;
    }
    if (set_socket_info(s_info) == NULL)
        return NULL;
    return s_info;
}
