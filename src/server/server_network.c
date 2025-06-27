#include "../../include/server/network.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static struct client *ai_clients = NULL;
static struct client *gui_clients = NULL;

static void add_client(struct client **lst, struct client *c)
{
    c->next = *lst;
    *lst = c;
}

int safe_write(int fd, const void *buf, size_t len)
{
    const char *p = buf;
    ssize_t ret;
    while (len > 0) {
        ret = write(fd, p, len);
        if (ret < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return 1;
            return -1;
        }
        if (ret == 0)
            return -1;
        p += ret;
        len -= (size_t)ret;
    }
    return 0;
}

void send_gui_event(const char *fmt, ...)
{
    char buf[512];
    va_list ap;
    struct client *c;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    for (c = gui_clients; c; c = c->next)
        safe_write(c->fd, buf, strlen(buf));
}

void handle_new_connection(int listen_fd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int fd = accept(listen_fd, (struct sockaddr *)&addr, &len);
    if (fd < 0)
        return;

    struct client *c = calloc(1, sizeof(*c));
    if (!c) {
        close(fd);
        return;
    }
    c->fd = fd;
    c->is_gui = false;
    c->next = NULL;

    add_client(&ai_clients, c);
}

void handle_readable_client(struct client *c)
{
    ssize_t ret = read(c->fd, c->rbuf + c->rlen, sizeof(c->rbuf) - c->rlen - 1);
    if (ret <= 0) {
        disconnect_client(c);
        return;
    }
    c->rlen += (size_t)ret;
    c->rbuf[c->rlen] = '\0';

    if (strcmp(c->rbuf, "GRAPHIC\n") == 0) {
        c->is_gui = true;
        c->rlen = 0;
        add_client(&gui_clients, c);
    }
}

void disconnect_client(struct client *c)
{
    close(c->fd);
    free(c);
}

