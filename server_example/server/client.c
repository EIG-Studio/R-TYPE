/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** client
*/

#include "server.h"

int handle_client_connect(server_info_t *s_info)
{
    struct sockaddr_in soc_info;
    int client_socket = 0;
    socklen_t l = sizeof(soc_info);

    if ((client_socket = accept(s_info->server_socket,
        (struct sockaddr *)&soc_info, (socklen_t *)&l)) < 0) {
        perror("accept");
        return 0;
    }
    if (s_info->clients[0]->client_socket == 0) {
        s_info->clients[0]->client_socket = client_socket;
    } else if (s_info->clients[1]->client_socket == 0) {
        s_info->clients[1]->client_socket = client_socket;
    } else {
        close(client_socket);
        return 0;
    }
    return client_socket;
}

static int manage_client(server_info_t *s_info, int client_socket,
    fd_set *write_fds)
{
    handle_client_io(client_socket, s_info, write_fds);
    return client_socket;
}

int handle_socket(server_info_t *s_info, fd_set *read_fds,
    fd_set *write_fds, int client_socket)
{
    int socket;

    if (client_socket == s_info->server_socket) {
        socket = handle_client_connect(s_info);
        if (socket != 0) {
            printf("Connection to a new client\n");
            FD_SET(client_socket, read_fds);
        }
        return socket;
    } else {
        return manage_client(s_info, client_socket, write_fds);
    }
}
