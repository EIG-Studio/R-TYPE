/*
** EPITECH PROJECT, 2023
** Main
** File description:
** Main file
*/

#include "server.h"
#include <signal.h>

void  close_with_ctrl_c(int sig)
{
    signal(sig, SIG_IGN);
    exit(0);
}

int help(void)
{
    printf("USAGE: ./myftp -p <port> -g <gravity> -m <map>\n");
    printf("\t-p  is the port number on which the server socket listens\n");
    printf("\t-g  is the gravity for the game\n");
    printf("\t-m  file for the map\n");
    return 0;
}

int main(int argc, char *const *argv)
{
    server_info_t *s_info = malloc(sizeof(server_info_t));
    int ret = 0;

    signal(SIGINT, close_with_ctrl_c);
    if (argc == 2 && (strcmp(argv[1], "-help") == 0))
        return help();
    if (argc == 7) {
        s_info = create_server(argv);
        if (s_info == NULL)
            return 84;
        printf("Server Launched.\n");
        ret = server_loop(s_info);
        close(s_info->server_socket);
        printf("Close server\n");
        free_struct(s_info);
    } else {
        ret = 84;
    }
    return ret;
}
