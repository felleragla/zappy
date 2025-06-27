/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** parse_teams.c
*/

#include "../../include/server/parser.h"

int parse_height(int ac, char **av, int *i, server_config_t *config)
{
    ++(*i);
    config->height = atoi(av[(*i)]);
    if (config->height <= 0) {
        fprintf(stderr, "Error: Height must be positive\n");
        return -1;
    }
    return 0;
}

int count_teams(int ac, char **av, int *i)
{
    int count = 0;
    int j = *i + 1;

    while (j < ac && av[j][0] != '-') {
        count++;
        j++;
    }
    return count;
}

int parse_teams(int ac, char **av, int *i, server_config_t *config)
{
    int j = 0;

    config->team_count = count_teams(ac, av, i);
    config->team_names = (char **)malloc((config->team_count + 1) * sizeof(char *));
    if (!config->team_names)
        return -1;
    for (j = 0; j < config->team_count; j++) {
        if (strcmp(av[*i + 1 + j], "GRAPHIC") == 0)
            return -1;
        config->team_names[j] = strdup(av[*i + 1 + j]);
        if (!config->team_names[j])
            return -1;
    }
    config->team_names[config->team_count] = NULL;
    *i += config->team_count;
    return 0;
}

int parse_clients(int ac, char **av, int *i, server_config_t *config)
{
    (void)ac;
    ++(*i);
    config->clients_per_team = atoi(av[(*i)]);
    if (config->clients_per_team <= 0) {
        fprintf(stderr, "Error: Clients per team must > 0\n");
        return -1;
    }
    return 0;
}

int parse_freq(int ac, char **av, int *i, server_config_t *config)
{
    (void)ac;
    ++(*i);
    config->freq = atoi(av[(*i)]);
    if (config->freq <= 0) {
        fprintf(stderr, "Error: Frequency must > 0\n");
        return -1;
    }
    return 0;
}
