/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** parser.c
*/

#include "../../include/server/parser.h"

void print_usage(const char *args)
{
    fprintf(stderr, "USAGE:%s -p port -x width -y height", args); 
    fprintf(stderr, "-n name1 name2 ... -c clientsNb -f freq\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -p port        Port number\n");
    fprintf(stderr, "  -x width       Width of the world\n");
    fprintf(stderr, "  -y height      Height of the world\n");
    fprintf(stderr, "  -n name1 name2 ...  Name of the teams\n");
    fprintf(stderr, "  -c clientsNb   Number of authorized clients per team\n");
    fprintf(stderr, "  -f freq        Reciprocal of time unit for execution of actions\n");
}

int check_help(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        print_usage(av[0]);
        return 1;
    }
    return 0;
}

int parse_port(int ac, char **av, int *i, server_config_t *config)
{
    ++(*i);
    config->port = atoi(av[(*i)]);
    printf("port: %d\n", config->port);
    if (config->port <= 0) {
        fprintf(stderr, "Error: Port must be positive\n");
        return -1;
    }
    return 0;
}

int parse_width(int ac, char **av, int *i, server_config_t *config)
{
    ++(*i);
    config->width = atoi(av[(*i)]);
    if (config->width <= 0) {
        fprintf(stderr, "Error: Width must be positive\n");
        return -1;
    }
    return 0;
}

int is_valid_option(char *arg)
{
    if (!arg || arg[0] != '-')
        return 0;
    if (strcmp(arg, "-p") == 0)
        return 1;
    if (strcmp(arg, "-x") == 0)
        return 1;
    if (strcmp(arg, "-y") == 0)
        return 1;
    if (strcmp(arg, "-n") == 0)
        return 1;
    if (strcmp(arg, "-c") == 0)
        return 1;
    if (strcmp(arg, "-f") == 0)
        return 1;
    return 0;
}