/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** players.h
*/

#ifndef PLAYERS_H
    #define PLAYERS_H
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include "maping.h"
    #include "parser.h"
    #include "event.h"

struct server_s;
struct player_s;

typedef enum {
    CLIENT_AI,
    CLIENT_GUI
} client_type_t;

typedef enum {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct resource {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} resource_t;

typedef struct {
    char *name;
    int duration;
    void (*handler)(struct server_s *, struct player_s *, char *);
} command_t;

typedef struct {
    command_t *cmd;
    double exec_time;
    char *arg;
} command_list_t;

typedef struct player_s {
    int x, y;
    orientation_t orient;
    resource_t inventory;
    int level;
    int team_idx;
    int fd;
    bool is_alive;
    client_type_t client_type;
    command_list_t *commands;
    int command_count;
} player_t;

typedef struct server_s {
    map_t *map;
    server_config_t *config;
    event_t *events;
    int event_count;
    player_t **players;
    int player_count;
} server_t;

void init_command_queue(player_t *player);
int is_valid_command(char *name, command_t *commands, int cmd_count);
command_t *find_command(char *name, command_t *commands, int cmd_count);

#endif
