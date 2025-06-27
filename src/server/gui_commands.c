/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** gui_commands.c
*/

#include "../../include/server/server.h"
#include "../../include/server/include.h"
#include <stdio.h>

// Helper function to find player by fd
static player_t *find_player_by_fd(server_t *server, int fd) {
    for (int i = 0; i < server->client_count; i++) {
        if (server->clients[i].fd == fd && server->clients[i].player) {
            return server->clients[i].player;
        }
    }
    return NULL;
}

void cmd_msz(server_t *server, client_t *client, char **args)
{
    (void)args;
    char response[64];
    snprintf(response, sizeof(response), "msz %d %d\n", server->config->width, server->config->height);
    send_to_client(client->fd, response);
}

void cmd_bct(server_t *server, client_t *client, char **args)
{

    if (args[1] == NULL || args[2] == NULL) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    int x = atoi(args[1]);
    int y = atoi(args[2]);
        
    if (x < 0 || x >= server->config->width || y < 0 || y >= server->config->height) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    tile_t *tile = &server->map->tiles[y][x];
    char response[256];
    snprintf(response, sizeof(response), "bct %d %d", x, y);
    
    char temp[32];
    snprintf(temp, sizeof(temp), " %d %d %d %d %d %d %d", 
             tile->food, tile->linemate, tile->deraumere, 
             tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
    strcat(response, temp);
    strcat(response, "\n");
    
    send_to_client(client->fd, response);
}

void cmd_mct(server_t *server, client_t *client, char **args)
{
    (void)args;
    
    for (int y = 0; y < server->config->height; y++) {
        for (int x = 0; x < server->config->width; x++) {
            tile_t *tile = &server->map->tiles[y][x];
            char response[256];
            snprintf(response, sizeof(response), "bct %d %d", x, y);
            
            char temp[32];
            snprintf(temp, sizeof(temp), " %d %d %d %d %d %d %d", 
                     tile->food, tile->linemate, tile->deraumere, 
                     tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
            strcat(response, temp);
            strcat(response, "\n");
            
            send_to_client(client->fd, response);
        }
    }
}

void cmd_tna(server_t *server, client_t *client, char **args)
{
    (void)args;
    
    for (int i = 0; i < server->config->team_count; i++) {
        char response[256];
        snprintf(response, sizeof(response), "tna %s\n", server->config->team_names[i]);
        send_to_client(client->fd, response);
    }
}

void cmd_ppo(server_t *server, client_t *client, char **args)
{
    if (!args[1]) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    int player_id = atoi(args[1]);
    player_t *player = find_player_by_fd(server, player_id);
    
    if (!player || !player->is_alive) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    char response[128];
    snprintf(response, sizeof(response), "ppo %d %d %d %d\n",
             player->fd, player->x, player->y, player->orient);
    send_to_client(client->fd, response);
}

void cmd_plv(server_t *server, client_t *client, char **args)
{
    if (!args[1]) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    int player_id = atoi(args[1]);
    player_t *player = find_player_by_fd(server, player_id);
    
    if (!player || !player->is_alive) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    char response[64];
    snprintf(response, sizeof(response), "plv %d %d\n", player->fd, player->level);
    send_to_client(client->fd, response);
}

void cmd_pin(server_t *server, client_t *client, char **args)
{
    if (!args[1]) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    int player_id = atoi(args[1]);
    player_t *player = find_player_by_fd(server, player_id);
    
    if (!player || !player->is_alive) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    char response[512];
    snprintf(response, sizeof(response), "pin %d %d %d", 
             player->fd, player->x, player->y);
    
    char temp[256];
    snprintf(temp, sizeof(temp), " %d %d %d %d %d %d %d", 
             player->inventory.food, player->inventory.linemate, 
             player->inventory.deraumere, player->inventory.sibur, 
             player->inventory.mendiane, player->inventory.phiras, 
             player->inventory.thystame);
    strcat(response, temp);
    strcat(response, "\n");
    
    send_to_client(client->fd, response);
}

void cmd_sgt(server_t *server, client_t *client, char **args)
{
    (void)args;
    char response[64];
    snprintf(response, sizeof(response), "sgt %d\n", server->config->freq);
    send_to_client(client->fd, response);
}

void cmd_sst(server_t *server, client_t *client, char **args)
{
    if (!args[1]) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    int new_freq = atoi(args[1]);
    if (new_freq <= 0 || new_freq > 10000) {
        send_to_client(client->fd, "sbp\n");
        return;
    }
    
    server->config->freq = new_freq;
    
    char response[64];
    snprintf(response, sizeof(response), "sst %d\n", server->config->freq);
    send_to_client(client->fd, response);
}