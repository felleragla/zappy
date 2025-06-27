/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** server.c
*/

#include "../../include/server/event.h"
#include <unistd.h>
#include "../../include/server/server.h"

void get_map_toroidal(map_t *map, int *x, int *y)
{
    *x = (*x + map->width) % map->width;
    *y = (*y + map->height) % map->height;
}

int init_server(server_t *server, server_config_t *config)
{
    server->config = config;
    server->map = create_map(config->width, config->height);
    if (!server->map)
        return -1;
    if (init_map_tiles(server->map) < 0)
        return -1;
    generate_resources(server->map, 1);
    init_events(&server->events, &server->event_count);
    return 0;
}

void run_server_loop(server_t *server)
{
    double now;

    while (1) {
        now = get_current_time();
        check_all_events(server, now);
        usleep(10000);
    }
}

void post_init_server(server_t *server)
{
    schedule_resource_event(server->map, server->config->freq,
        server->events, &server->event_count);
}
