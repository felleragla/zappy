/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-andy.sagbo
** File description:
** Include.hpp
*/

#ifndef _ZAPPY_SERVER_
    #define _ZAPPY_SERVER_
    #define MAX_CLIENTS 50
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include "parser.h"

void usage(void);
int server(server_config_t config);

#endif /*_ZAPPY_SERVER_*/
