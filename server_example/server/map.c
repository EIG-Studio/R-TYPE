/*
** EPITECH PROJECT, 2023
** B-SYN-400-BDX-4-1-jetpack2tek3-quentin.charpentier
** File description:
** map
*/

#include "map.h"

static map_t *init_struct_map(map_t *map, char const *mapfile)
{
    struct stat st;

    if (stat(mapfile, &st) == -1)
        return NULL;
    map->size = st.st_size;
    map->height = 0;
    map->width = 0;
    map->cells = malloc(sizeof(char) * map->size + 1);
    return map;
}

static void mapfiletostr(map_t *map)
{
    int chrrmv = 0;

    for (; map->cells[map->width] != '\n'; map->width++) {}
    for (int idx = 0; map->cells[idx] != '\0'; idx++) {
        if (map->cells[idx] == '\n' || map->cells[idx + 1] == '\0') {
            map->height++;
        }
        if (map->cells[idx] != '_' && map->cells[idx] != 'e' &&
            map->cells[idx] != 'c' && map->cells[idx] != '\n') {
            map->cells[chrrmv++] = '_';
        }
        if (map->cells[idx] != '\n') {
            map->cells[chrrmv++] = map->cells[idx];
        }
    }
    map->cells[chrrmv] = '\0';
}

map_t *get_map(char const *mapfile)
{
    map_t *map = malloc(sizeof(map_t));
    int fd = 0;

    if (mapfile == NULL) {
        free(map);
        return NULL;
    }
    map = init_struct_map(map, mapfile);
    if (!map || map->size <= 0)
        return NULL;
    fd = open(mapfile, O_RDONLY);
    if (fd <= 0)
        return NULL;
    read(fd, map->cells, map->size);
    map->cells[map->size] = '\0';
    close(fd);
    mapfiletostr(map);
    if (map->height < 10)
        return NULL;
    return map;
}
