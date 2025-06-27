/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** parser.h
*/

#ifndef PARSER_H
    #define PARSER_H
    #include <string.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

typedef struct config{
    int port;
    int width;
    int height;
    char **team_names;
    int team_count;
    int clients_per_team;
    int freq;
} server_config_t;

void free_config(server_config_t *config);
int parse_args(int ac, char **av, server_config_t *config);
void print_usage(const char *args);
int is_valid_option(char *option);
int check_help(int ac, char **av);
int parse_port(int ac, char **av, int *i, server_config_t *config);
int parse_width(int ac, char **av, int *i, server_config_t *config);
int parse_height(int ac, char **av, int *i, server_config_t *config);
int parse_teams(int ac, char **av, int *i, server_config_t *config);
int parse_clients(int ac, char **av, int *i, server_config_t *config);
int parse_freq(int ac, char **av, int *i, server_config_t *config);
#endif