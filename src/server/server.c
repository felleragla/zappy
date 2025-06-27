/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** server.c
*/

#include "../../include/server/include.h"

int sock(int prt)
{
    int bin = 0;
    int fd = 0;
    struct sockaddr_in server_addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(prt);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bin = bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    return fd;
}

void send_cmd(int client_fd)
{
    char *msz = "msz 10 10\n";
    char *bct1 = "bct 0 0 1 1 1 1 1 1 1\n";
    char *bct2 = "bct 0 9 1 1 1 1 1 1 1\n";
    char *bct3 = "bct 0 4 1 1 1 1 1 1 1\n";
    char *bct4 = "bct 1 4 1 1 1 1 1 1 1\n";
    char *bct5 = "bct 3 6 1 1 1 1 1 1 1\n";
    char *bct6 = "bct 2 5 1 1 1 1 1 1 1\n";
    char *bct7 = "bct 6 6 1 1 1 1 1 1 1\n";

    send(client_fd, msz, strlen(msz), 0);
    send(client_fd, bct1, strlen(bct1), 0);
    send(client_fd, bct2, strlen(bct2), 0);
    send(client_fd, bct3, strlen(bct3), 0);
    send(client_fd, bct4, strlen(bct4), 0);
    send(client_fd, bct5, strlen(bct5), 0);
    send(client_fd, bct6, strlen(bct6), 0);
    send(client_fd, bct7, strlen(bct7), 0);
}

void handle_gui_client(int client_fd)
{
    printf("GUI client connected\n");
    send_cmd(client_fd);
    // Keep connection open for GUI commands
}

void handle_ai_client(int client_fd, char *buffer)
{
    printf("AI client connected with message: %s\n", buffer);
    send(client_fd, "WELCOME\n", 8, 0);
    // Process AI client commands here
    close(client_fd);
}

void handle_client(int client_fd, struct sockaddr_in client_addr)
{
    char buffer[1024];
    int recv_;

    printf("connection from %s\n", inet_ntoa(client_addr.sin_addr));
    if (client_fd < 0)
        return;
    
    memset(buffer, 0, sizeof(buffer));
    recv_ = read(client_fd, buffer, sizeof(buffer));
    if (recv_ > 0) {
        buffer[recv_] = '\0';
        printf("I receive: %s\n", buffer);
        
        // Check if it's a GUI client
        if (strcmp(buffer, "GRAPHIC\n") == 0) {
            handle_gui_client(client_fd);
        } else {
            // It's an AI client
            handle_ai_client(client_fd, buffer);
        }
    } else {
        close(client_fd);
    }
}

int server(server_config_t stc)
{
    int fd = 0;
    int list = 0;
    int client_fd = 0;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    fd_set readfds;
    int max_fd;
    int gui_clients[MAX_CLIENTS];
    int gui_count = 0;
    int i;

    // Initialize GUI clients array
    for (i = 0; i < MAX_CLIENTS; i++) {
        gui_clients[i] = -1;
    }

    fd = sock(stc.port);
    list = listen(fd, 20);
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        max_fd = fd;
        
        // Add GUI clients to select
        for (i = 0; i < gui_count; i++) {
            if (gui_clients[i] != -1) {
                FD_SET(gui_clients[i], &readfds);
                if (gui_clients[i] > max_fd) {
                    max_fd = gui_clients[i];
                }
            }
        }
        
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            break;
        }
        
        // Check for new connections
        if (FD_ISSET(fd, &readfds)) {
            client_fd = accept(fd, (struct sockaddr*)&(client_addr), &client_len);
            if (client_fd >= 0) {
                char buffer[1024];
                int recv_;
                
                printf("connection from %s\n", inet_ntoa(client_addr.sin_addr));
                memset(buffer, 0, sizeof(buffer));
                recv_ = read(client_fd, buffer, sizeof(buffer));
                
                if (recv_ > 0) {
                    buffer[recv_] = '\0';
                    printf("I receive: %s\n", buffer);
                    
                    if (strcmp(buffer, "GRAPHIC\n") == 0) {
                        // Add GUI client to persistent connections
                        if (gui_count < MAX_CLIENTS) {
                            gui_clients[gui_count] = client_fd;
                            gui_count++;
                            printf("GUI client connected and added to persistent connections\n");
                            send_cmd(client_fd);
                        } else {
                            printf("Maximum GUI clients reached\n");
                            close(client_fd);
                        }
                    } else {
                        // Handle AI client
                        printf("AI client connected with message: %s\n", buffer);
                        send(client_fd, "WELCOME\n", 8, 0);
                        close(client_fd);
                    }
                } else {
                    close(client_fd);
                }
            }
        }
        
        // Check GUI clients for commands
        for (i = 0; i < gui_count; i++) {
            if (gui_clients[i] != -1 && FD_ISSET(gui_clients[i], &readfds)) {
                char buffer[1024];
                int recv_ = read(gui_clients[i], buffer, sizeof(buffer));
                
                if (recv_ <= 0) {
                    // GUI client disconnected
                    printf("GUI client disconnected\n");
                    close(gui_clients[i]);
                    gui_clients[i] = -1;
                } else {
                    buffer[recv_] = '\0';
                    printf("GUI command received: %s\n", buffer);
                    // Process GUI commands here
                }
            }
        }
    }
    
    close(fd);
    return 0;
}