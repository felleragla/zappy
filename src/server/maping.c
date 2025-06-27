/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** maping.c
*/

#include "../../include/server/maping.h"
#include <time.h>

map_t *create_map(int width, int height)
{
    map_t *map;

    map = (map_t *)malloc(sizeof(map_t));
    if (!map)
        return NULL;
    map->width = width;
    map->height = height;
    map->tiles = (tile_t **)malloc(height * sizeof(tile_t *));
    if (!map->tiles) {
        free(map);
        return NULL;
    }
    return map;
}

int init_map_tiles(map_t *map)
{
    int y = 0;

    while (y < map->height) {
        map->tiles[y] = (tile_t *)malloc(map->width * sizeof(tile_t));
        if (!map->tiles[y])
            return -1;
        memset(map->tiles[y], 0, map->width * sizeof(tile_t));
        y++;
    }
    return 0;
}

void free_map(map_t *map)
{
    int y = 0;

    if (!map)
        return;
    while (y < map->height) {
        free(map->tiles[y]);
        y++;
    }
    free(map->tiles);
    free(map);
}

int handle_resource_amount(int total, double density, int ensure_min)
{
    int amount;

    amount = (int)(total * density);
    if (ensure_min && amount < 1)
        return 1;
    return amount;
}

void distribute_resource(map_t *map, int amount, int type)
{
    int j = 0;
    int x = 0;
    int y = 0;

    for (j; j < amount; j++) {
        x = rand() % map->width;
        y = rand() % map->height;
        if (type == 0)
            map->tiles[y][x].food++;
        if (type == 1)
            map->tiles[y][x].linemate++;
        if (type == 2)
            map->tiles[y][x].deraumere++;
        if (type == 3)
            map->tiles[y][x].sibur++;
        if (type == 4)
            map->tiles[y][x].mendiane++;
        if (type == 5)
            map->tiles[y][x].phiras++;
        if (type == 6)
            map->tiles[y][x].thystame++;
    }
}

void generate_resources(map_t *map, int ensure_min)
{
    int total;

    total = map->width * map->height;
    srand(time(NULL));
    distribute_resource(map, handle_resource_amount(total, 0.5,
        ensure_min), 0);
    distribute_resource(map, handle_resource_amount(total, 0.3,
        ensure_min), 1);
    distribute_resource(map, handle_resource_amount(total, 0.15,
        ensure_min), 2);
    distribute_resource(map, handle_resource_amount(total, 0.1,
        ensure_min), 3);
    distribute_resource(map, handle_resource_amount(total, 0.1,
        ensure_min), 4);
    distribute_resource(map, handle_resource_amount(total, 0.08,
        ensure_min), 5);
    distribute_resource(map, handle_resource_amount(total, 0.05,
        ensure_min), 6);
}
