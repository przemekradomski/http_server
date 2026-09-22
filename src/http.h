#ifndef HTTP_H
#define HTTP_H

#define HTTP_METHOD_SIZE 16
#define HTTP_PATH_SIZE 256
#define HTTP_VERSION_SIZE 16

typedef struct {
    char method[HTTP_METHOD_SIZE];
    char path[HTTP_PATH_SIZE];
    char version[HTTP_VERSION_SIZE];
} HTTPRequest;

int http_parse_request(const char *request_str, HTTPRequest * request);

#endif