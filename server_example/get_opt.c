/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** get_opt
*/

#include "server.h"

static char **copy_opt(char **list_opt, int idx_opt, char *opt_arg)
{
    list_opt[idx_opt] = malloc(sizeof(char) * strlen(opt_arg) + 1);
    strcpy(list_opt[idx_opt], opt_arg);
    list_opt[idx_opt][strlen(opt_arg)] = '\0';
    return list_opt;
}

static char **switch_opt(char **list_opt, int tmp_opt)
{
    switch (tmp_opt) {
        case 'p':
            list_opt = copy_opt(list_opt, 0, optarg);
            break;
        case 'g':
            list_opt = copy_opt(list_opt, 1, optarg);
            break;
        case 'm':
            list_opt = copy_opt(list_opt, 2, optarg);
            break;
        case ':':
            printf("Need Argument for option\n");
            break;
        case '?':
            return NULL;
    }
    return list_opt;
}

char **get_opt(char *const *opt)
{
    int tmp_opt;
    char **list_opt = malloc(sizeof(char*) * 4);
    for (int idx = 0; idx < 4; idx++) {
        list_opt[idx] = NULL;
    }
    while ((tmp_opt = getopt(7, opt, "-p:-g:-m:")) != -1) {
        list_opt = switch_opt(list_opt, tmp_opt);
    }
    if (!list_opt)
        return NULL;
    for (int idx = 0; idx < 3; idx++) {
        if (list_opt[idx] == NULL)
            return NULL;
    }
    return list_opt;
}
