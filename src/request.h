#ifndef REQUEST_H
#define REQUEST_H

#define REQUEST_METHOD_SIZE 16
#define REQUEST_PATH_SIZE 256
#define REQUEST_VERSION_SIZE 16

typedef struct
{
    char method[REQUEST_METHOD_SIZE];
    char path[REQUEST_PATH_SIZE];
    char version[REQUEST_VERSION_SIZE];
} HttpRequest;

int request_parse(const char *buffer, HttpRequest *request);

#endif