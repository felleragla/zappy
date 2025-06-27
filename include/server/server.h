/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H
    #include <stdbool.h>
    #include <stdio.h>
    #include "event.h"
    #include "maping.h"
    #include "players.h"

// typedef struct {
//     int port, width, height;
//     char **team_names;
//     int team_count, clients_per_team, freq;
// } server_config_t;

void check_all_events(server_t *server, double now);
void post_init_server(server_t *server);
void run_server_loop(server_t *server);
int init_server(server_t *server, server_config_t *config);

#endif
