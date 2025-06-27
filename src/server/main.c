/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** server.c
*/

#include "../../include/server/parser.h"
#include "../../include/server/include.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    server_config_t config = {0};

    if (parse_args(argc, argv, &config) < 0) {
        free_config(&config);
        return 84;
    }

    // Afficher les arguments pour vérification
    printf("Port: %d\n", config.port);
    printf("Width: %d\n", config.width);
    printf("Height: %d\n", config.height);
    printf("Teams: ");
    for (int i = 0; i < config.team_count; i++) {
        printf("%s ", config.team_names[i]);
    }
    printf("\nClients per team: %d\n", config.clients_per_team);
    printf("Frequency: %d\n", config.freq);
    server(config);
    // Initialiser le serveur avec la configuration
    // ... (code pour lancer le serveur)

    free_config(&config);
    return 0;
}