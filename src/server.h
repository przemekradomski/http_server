#ifndef SERVER_H
#define SERVER_H

#define SERVER_PORT 8080
#define SERVER_BACKLOG 10

int server_create(void);
int server_accept(int server_fd);

#endif