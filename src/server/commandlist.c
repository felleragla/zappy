/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** commandlist.c
*/

#include <string.h>
#include "../../include/server/server.h"
#include "../../include/server/maping.h"
#include "../../include/server/players.h"
#include "../../include/server/event.h"
#include <stdlib.h>

void init_command_queue(player_t *player)
{
    player->commands = (command_list_t *)malloc(10 * sizeof(command_list_t));
    if (!player->commands)
        exit(84);
    player->command_count = 0;
}

int is_valid_command(char *name, command_t *commands, int cmd_count)
{
    int i = 0;

    while (i < cmd_count) {
        if (strcmp(name, commands[i].name) == 0)
            return 1;
        i++;
    }
    return 0;
}

command_t *find_command(char *name, command_t *commands, int cmd_count)
{
    int i = 0;

    while (i < cmd_count) {
        if (strcmp(name, commands[i].name) == 0)
            return &commands[i];
        i++;
    }
    return NULL;
}

int queue_command(player_t *player, command_t *cmd, double freq, char *arg)
{
    command_list_t *qc;

    if (player->command_count >= 10)
        return -1;
    qc = &player->commands[player->command_count];
    qc->cmd = cmd;
    qc->exec_time = get_current_time() + (cmd->duration / freq);
    if (arg != NULL) {
        qc->arg = strdup(arg);
        if (qc->arg == NULL)
            return -1;
    } else {
        qc->arg = NULL;
    }
    player->command_count++;
    return 0;
}