/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo [WSL: Ubuntu]
** File description:
** commands.c
*/

#include "../../include/server/include.h"
#include "../../include/server/server.h"
#include "../../include/server/players.h"
#include "../../include/server/maping.h"
#include "../../include/server/event.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// Forward declaration
void broadcast_to_gui(server_t *server, const char *message);


// Movement commands
void cmd_forward(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    int new_x = player->x;
    int new_y = player->y;
    
    // Calculate new position based on orientation
    switch (player->orient) {
        case NORTH: new_y = (new_y - 1 + server->map->height) % server->map->height; break;
        case SOUTH: new_y = (new_y + 1) % server->map->height; break;
        case EAST: new_x = (new_x + 1) % server->map->width; break;
        case WEST: new_x = (new_x - 1 + server->map->width) % server->map->width; break;
    }
    
    player->x = new_x;
    player->y = new_y;
    
    send_to_client(player->fd, "ok\n");
    
    // Notify GUI
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo #%d %d %d %d\n", 
             player->fd, player->x, player->y, player->orient);
    broadcast_to_gui(server, gui_msg);
}

void cmd_right(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    player->orient = (player->orient + 1) % 4;
    
    send_to_client(player->fd, "ok\n");
    
    // Notify GUI
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo #%d %d %d %d\n", 
             player->fd, player->x, player->y, player->orient);
    broadcast_to_gui(server, gui_msg);
}

void cmd_left(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    player->orient = (player->orient - 1 + 4) % 4;
    
    send_to_client(player->fd, "ok\n");
    
    // Notify GUI
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "ppo #%d %d %d %d\n", 
             player->fd, player->x, player->y, player->orient);
    broadcast_to_gui(server, gui_msg);
}

// Information commands
void cmd_look(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    char response[1024] = "[";
    int level = player->level;
    int x = player->x;
    int y = player->y;
    
    // Look around based on player level and orientation
    for (int i = 0; i <= level; i++) {
        for (int j = -i; j <= i; j++) {
            int look_x = x, look_y = y;
            
            // Calculate position based on orientation
            switch (player->orient) {
                case NORTH:
                    look_x = (x + j + server->map->width) % server->map->width;
                    look_y = (y - i + server->map->height) % server->map->height;
                    break;
                case SOUTH:
                    look_x = (x - j + server->map->width) % server->map->width;
                    look_y = (y + i) % server->map->height;
                    break;
                case EAST:
                    look_x = (x + i) % server->map->width;
                    look_y = (y + j + server->map->height) % server->map->height;
                    break;
                case WEST:
                    look_x = (x - i + server->map->width) % server->map->width;
                    look_y = (y - j + server->map->height) % server->map->height;
                    break;
            }
            
            tile_t *tile = &server->map->tiles[look_y][look_x];
            
            if (strlen(response) > 1) strcat(response, ",");
            
            char tile_content[256] = "";
            for (int f = 0; f < tile->food; f++) strcat(tile_content, "food ");
            for (int l = 0; l < tile->linemate; l++) strcat(tile_content, "linemate ");
            for (int d = 0; d < tile->deraumere; d++) strcat(tile_content, "deraumere ");
            for (int s = 0; s < tile->sibur; s++) strcat(tile_content, "sibur ");
            for (int m = 0; m < tile->mendiane; m++) strcat(tile_content, "mendiane ");
            for (int p = 0; p < tile->phiras; p++) strcat(tile_content, "phiras ");
            for (int t = 0; t < tile->thystame; t++) strcat(tile_content, "thystame ");
            
            // Remove trailing space
            int len = strlen(tile_content);
            if (len > 0 && tile_content[len-1] == ' ') tile_content[len-1] = '\0';
            
            strcat(response, tile_content);
        }
    }
    
    strcat(response, "]\n");
    send_to_client(player->fd, response);
}

void cmd_inventory(server_t *server, player_t *player, char *arg)
{
    (void)server;
    (void)arg;
    
    char response[256];
    snprintf(response, sizeof(response), 
             "[food %d,linemate %d,deraumere %d,sibur %d,mendiane %d,phiras %d,thystame %d]\n",
             player->inventory.food, player->inventory.linemate, player->inventory.deraumere,
             player->inventory.sibur, player->inventory.mendiane, player->inventory.phiras,
             player->inventory.thystame);
    
    send_to_client(player->fd, response);
    
    // Notify GUI
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pin #%d %d %d %d %d %d %d %d %d %d\n",
             player->fd, player->x, player->y, player->inventory.food,
             player->inventory.linemate, player->inventory.deraumere,
             player->inventory.sibur, player->inventory.mendiane,
             player->inventory.phiras, player->inventory.thystame);
    broadcast_to_gui(server, gui_msg);
}

// Communication commands
void cmd_broadcast(server_t *server, player_t *player, char *arg)
{
    if (!arg) {
        send_to_client(player->fd, "ko\n");
        return;
    }
    
    send_to_client(player->fd, "ok\n");
    
    // Notify GUI
    char gui_msg[512];
    snprintf(gui_msg, sizeof(gui_msg), "pbc #%d %s\n", player->fd, arg);
    broadcast_to_gui(server, gui_msg);
    
    // TODO: Send broadcast to other players with direction calculation
}

void cmd_connect_nbr(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    
    // Count available slots for player's team
    int team_players = 0;
    for (int i = 0; i < server->player_count; i++) {
        if (server->players[i] && server->players[i]->team_idx == player->team_idx) {
            team_players++;
        }
    }
    
    int available_slots = server->config->clients_per_team - team_players;
    if (available_slots < 0) available_slots = 0;
    
    char response[32];
    snprintf(response, sizeof(response), "%d\n", available_slots);
    send_to_client(player->fd, response);
}

// Object manipulation commands
void cmd_take(server_t *server, player_t *player, char *arg)
{
    if (!arg) {
        send_to_client(player->fd, "ko\n");
        return;
    }
    
    tile_t *tile = &server->map->tiles[player->y][player->x];
    int taken = 0;
    
    if (strcmp(arg, "food") == 0 && tile->food > 0) {
        tile->food--;
        player->inventory.food++;
        taken = 1;
    } else if (strcmp(arg, "linemate") == 0 && tile->linemate > 0) {
        tile->linemate--;
        player->inventory.linemate++;
        taken = 1;
    } else if (strcmp(arg, "deraumere") == 0 && tile->deraumere > 0) {
        tile->deraumere--;
        player->inventory.deraumere++;
        taken = 1;
    } else if (strcmp(arg, "sibur") == 0 && tile->sibur > 0) {
        tile->sibur--;
        player->inventory.sibur++;
        taken = 1;
    } else if (strcmp(arg, "mendiane") == 0 && tile->mendiane > 0) {
        tile->mendiane--;
        player->inventory.mendiane++;
        taken = 1;
    } else if (strcmp(arg, "phiras") == 0 && tile->phiras > 0) {
        tile->phiras--;
        player->inventory.phiras++;
        taken = 1;
    } else if (strcmp(arg, "thystame") == 0 && tile->thystame > 0) {
        tile->thystame--;
        player->inventory.thystame++;
        taken = 1;
    }
    
    if (taken) {
        send_to_client(player->fd, "ok\n");
        
        // Notify GUI
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "pgt #%d %s\n", player->fd, arg);
        broadcast_to_gui(server, gui_msg);
        
        // Update tile content for GUI
        snprintf(gui_msg, sizeof(gui_msg), "bct %d %d %d %d %d %d %d %d %d\n",
                 player->x, player->y, tile->food, tile->linemate, tile->deraumere,
                 tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
        broadcast_to_gui(server, gui_msg);
    } else {
        send_to_client(player->fd, "ko\n");
    }
}

void cmd_set(server_t *server, player_t *player, char *arg)
{
    if (!arg) {
        send_to_client(player->fd, "ko\n");
        return;
    }
    
    tile_t *tile = &server->map->tiles[player->y][player->x];
    int set = 0;
    
    if (strcmp(arg, "food") == 0 && player->inventory.food > 0) {
        tile->food++;
        player->inventory.food--;
        set = 1;
    } else if (strcmp(arg, "linemate") == 0 && player->inventory.linemate > 0) {
        tile->linemate++;
        player->inventory.linemate--;
        set = 1;
    } else if (strcmp(arg, "deraumere") == 0 && player->inventory.deraumere > 0) {
        tile->deraumere++;
        player->inventory.deraumere--;
        set = 1;
    } else if (strcmp(arg, "sibur") == 0 && player->inventory.sibur > 0) {
        tile->sibur++;
        player->inventory.sibur--;
        set = 1;
    } else if (strcmp(arg, "mendiane") == 0 && player->inventory.mendiane > 0) {
        tile->mendiane++;
        player->inventory.mendiane--;
        set = 1;
    } else if (strcmp(arg, "phiras") == 0 && player->inventory.phiras > 0) {
        tile->phiras++;
        player->inventory.phiras--;
        set = 1;
    } else if (strcmp(arg, "thystame") == 0 && player->inventory.thystame > 0) {
        tile->thystame++;
        player->inventory.thystame--;
        set = 1;
    }
    
    if (set) {
        send_to_client(player->fd, "ok\n");
        
        // Notify GUI
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "pdr #%d %s\n", player->fd, arg);
        broadcast_to_gui(server, gui_msg);
        
        // Update tile content for GUI
        snprintf(gui_msg, sizeof(gui_msg), "bct %d %d %d %d %d %d %d %d %d\n",
                 player->x, player->y, tile->food, tile->linemate, tile->deraumere,
                 tile->sibur, tile->mendiane, tile->phiras, tile->thystame);
        broadcast_to_gui(server, gui_msg);
    } else {
        send_to_client(player->fd, "ko\n");
    }
}

// Advanced commands
void cmd_fork(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    
    send_to_client(player->fd, "ok\n");
    
    // Notify GUI
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pfk #%d\n", player->fd);
    broadcast_to_gui(server, gui_msg);
    
    // TODO: Create egg logic
}

void cmd_eject(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    
    // TODO: Find players on same tile and eject them
    int ejected = 0;
    
    for (int i = 0; i < server->player_count; i++) {
        if (server->players[i] && server->players[i] != player &&
            server->players[i]->x == player->x && server->players[i]->y == player->y) {
            ejected = 1;
            
            // Notify ejected player
            send_to_client(server->players[i]->fd, "eject\n");
            
            // Notify GUI
            char gui_msg[256];
            snprintf(gui_msg, sizeof(gui_msg), "pex #%d\n", server->players[i]->fd);
            broadcast_to_gui(server, gui_msg);
        }
    }
    
    if (ejected) {
        send_to_client(player->fd, "ok\n");
    } else {
        send_to_client(player->fd, "ko\n");
    }
}

void cmd_incantation(server_t *server, player_t *player, char *arg)
{
    (void)arg;
    
    // TODO: Check incantation requirements based on level
    // For now, simple implementation
    
    send_to_client(player->fd, "Elevation underway\n");
    
    // Notify GUI start
    char gui_msg[256];
    snprintf(gui_msg, sizeof(gui_msg), "pic %d %d %d #%d\n",
             player->x, player->y, player->level, player->fd);
    broadcast_to_gui(server, gui_msg);
    
    // TODO: Implement proper incantation logic with requirements check
    // For now, just increase level
    player->level++;
    
    // Notify GUI end
    snprintf(gui_msg, sizeof(gui_msg), "pie %d %d %d\n",
             player->x, player->y, 1); // 1 = success
    broadcast_to_gui(server, gui_msg);
    
    send_to_client(player->fd, "Current level: 2\n"); // TODO: use actual level
}

// Helper functions


void send_to_all_gui(server_t *server, const char *message)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd != -1 && 
            server->clients[i].type == CLIENT_GUI &&
            server->clients[i].authenticated) {
            send_to_client(server->clients[i].fd, message);
        }
    }
}

void broadcast_to_gui(server_t *server, const char *message)
{
    // TODO: Send message to all connected GUI clients
    (void)server;
    (void)message;
    // For now, just print to stdout for debugging
    printf("GUI: %s", message);
}