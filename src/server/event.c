/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** event.c
*/

#define _POSIX_C_SOURCE 199309L

#include "../../include/server/event.h"
#include "../../include/server/server.h"
#include <time.h>

double get_current_time(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void init_events(event_t **events, int *count)
{
    *events = (event_t *)malloc(10 * sizeof(event_t));
    if (*events == NULL)
        exit(84);
    *count = 0;
}

void schedule_resource_event(map_t *map, double freq, event_t *events,
    int *count)
{
    event_t *event;

    event = &events[*count];
    if (*count > 10)
        return;
    event->handler = generate_resources;
    event->next_time = get_current_time() + (20.0 / freq);
    (*count)++;
}

void execute_event(event_t *event, map_t *map, double freq)
{
    event->handler(map, (int)freq);
    event->next_time += 20.0 / freq;
    printf("Resources generated at %.2f seconds\n", get_current_time());
}

void check_single_event(event_t *event, map_t *map,
    double freq, double now)
{
    if (event->next_time >= now)
        return;
    execute_event(event, map, freq);
}

void check_all_events(server_t *server, double now)
{
    int i = 0;
    map_t map_struct;
    
    map_struct.width = server->config->width;
    map_struct.height = server->config->height;
    map_struct.tiles = server->map;

    while (i < server->event_count) {
        check_single_event(&server->events[i], &map_struct,
            server->config->freq, now);
        i++;
    }
}

void free_events(event_t *events)
{
    free(events);
}
