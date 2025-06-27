/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** event.h
*/

#ifndef EVENT_H
    #define EVENT_H
    #include <stdbool.h>
    #include "maping.h"
    #include "parser.h"
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>

typedef struct event {
    void (*handler)(map_t *map, int freq);
    double next_time;
} event_t;

double get_current_time(void);
void schedule_resource_event(map_t *map, double freq,
    event_t *events, int *event_count);
void init_events(event_t **events, int *count);
void execute_event(event_t *event, map_t *map, double freq);
static void check_single_event(event_t *event, map_t *map,
    double freq, double now);
void free_events(event_t *events);

#endif
