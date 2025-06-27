/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** parsing.c
*/

#include "../../include/server/parser.h"

void verification(char **av, int i, server_config_t *config)
{
    if (config->port == 0 || config->width == 0 || config->height == 0 ||
    !config->team_names || config->clients_per_team == 0) {
        fprintf(stderr, "Error: Missing required arguments\n");
        exit(-1);
    }
    if (!is_valid_option(av[i])) {
            fprintf(stderr, "Error: Invalid option %s\n", av[i]);
            exit(-1);
        }
}

int parse_args(int ac, char **av, server_config_t *config)
{
    //init_config(config);
    if (check_help(ac, av))
        return -1;
    for (int i = 1; i < ac; i++) {
        //verification(av, i, config);
        if (strcmp(av[i], "-p") == 0 &&
        parse_port(ac, av, &i, config) < 0)
            return -1;
        else if (strcmp(av[i], "-x") == 0 &&
        parse_width(ac, av, &i, config) < 0)
            return -1;
        else if (strcmp(av[i], "-y") == 0 &&
        parse_height(ac, av, &i, config) < 0)
            return -1;
        else if (strcmp(av[i], "-n") == 0 &&
        parse_teams(ac, av, &i, config) < 0)
            return -1;
        else if (strcmp(av[i], "-c") == 0 &&
        parse_clients(ac, av, &i, config) < 0)
            return -1;
        else if (strcmp(av[i], "-f") == 0 &&
        parse_freq(ac, av, &i, config) < 0)
            return -1;
    }
    return 0;
}

void free_config(server_config_t *config)
{
    for (int i = 0; i < config->team_count; i++)
        if (config->team_names[i])
            free(config->team_names[i]);
    free(config->team_names);
}
