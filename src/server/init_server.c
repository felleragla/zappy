#include "../../include/server/server.h"
#include "../../include/server/gui_commands.h"
#include <sys/socket.h>

int init_server(server_t *server, server_config_t *config)
{
    server->config = config;
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd == -1) {
        perror("socket");
        return -1;
    }

    int optval = 1;
    if (setsockopt(server->socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        close(server->socket_fd);
        return -1;
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(config->port);

    if (bind(server->socket_fd, (struct sockaddr *)&server->address, sizeof(server->address)) == -1) {
        perror("bind");
        close(server->socket_fd);
        return -1;
    }

    if (listen(server->socket_fd, 5) == -1) {
        perror("listen");
        close(server->socket_fd);
        return -1;
    }

    FD_ZERO(&server->master_fds);
    FD_SET(server->socket_fd, &server->master_fds);
    server->max_fd = server->socket_fd;

    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->gui_clients);
    TAILQ_INIT(&server->eggs);

    server->map = malloc(sizeof(tile_t *) * config->height);
    if (!server->map) {
        perror("malloc");
        close(server->socket_fd);
        return -1;
    }
    for (int i = 0; i < config->height; i++) {
        server->map[i] = malloc(sizeof(tile_t) * config->width);
        if (!server->map[i]) {
            perror("malloc");
            for (int j = 0; j < i; j++) free(server->map[j]);
            free(server->map);
            close(server->socket_fd);
            return -1;
        }
        for (int j = 0; j < config->width; j++) {
            for (int k = 0; k < NB_RESOURCES; k++) {
                server->map[i][j].resources[k] = 0;
            }
        }
    }

    server->teams = malloc(sizeof(team_t) * config->team_count);
    if (!server->teams) {
        perror("malloc");
        // Free map
        for (int i = 0; i < config->height; i++) free(server->map[i]);
        free(server->map);
        close(server->socket_fd);
        return -1;
    }
    for (int i = 0; i < config->team_count; i++) {
        server->teams[i].name = strdup(config->team_names[i]);
        server->teams[i].available_slots = config->clients_per_team;
        TAILQ_INIT(&server->teams[i].players);
    }

    server->last_resource_spawn = time(NULL);
    server->time_unit = 1.0 / config->freq;
    server->current_client_id = 0;
    server->current_egg_id = 0;

    return 0;
}

void post_init_server(server_t *server)
{
    (void)server;
}

void send_to_client(int fd, const char *message)
{
    send(fd, message, strlen(message), 0);
}

void check_all_events(server_t *server, double now)
{
    (void)server;
    (void)now;
}