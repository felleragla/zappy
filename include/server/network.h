#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>
#include <stddef.h>
#include <sys/poll.h>
#include "players.h"

struct client {
    int fd;
    bool is_gui;
    char rbuf[4096];
    size_t rlen;
    char wbuf[4096];
    size_t wlen;
    struct client *next;
};

int  safe_write(int fd, const void *buf, size_t len);
void send_gui_event(const char *fmt, ...);
void handle_new_connection(int listen_fd);
void handle_readable_client(struct client *c);
void disconnect_client(struct client *c);

#endif
