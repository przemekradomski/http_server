#ifndef RESPONSE_H
#define RESPONSE_H

int response_send(int client_fd, int status_code, const char *body);
int response_send_file(int client_fd, int status_code, const char *filename);

#endif