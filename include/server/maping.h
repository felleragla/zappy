/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** maping.h
*/

#ifndef MAPING_H
    #define MAPING_H
    #include <string.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "parser.h"

// struct player_t;
// struct egg_t;

typedef struct {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    // struct player_t **players;
    // struct egg_t **eggs;
} tile_t;

typedef struct map {
    int width;
    int height;
    tile_t **tiles;
} map_t;

map_t *create_map(int width, int height);
int init_map_tiles(map_t *map);
void free_map(map_t *map);
int handle_resource_amount(int total, double density, int ensure_min);
void distribute_resource(map_t *map, int amount, int type);
void generate_resources(map_t *map, int ensure_min);
void get_map_toroidal(map_t *map, int *x, int *y);
#endif
