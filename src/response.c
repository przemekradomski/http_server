#include "response.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int response_send(int client_fd, int status_code, const char *body)
{
    if (body == NULL)
    {
        return -1;
    }

    const char *status_text;

    switch (status_code)
    {
        case 200:
            status_text = "OK";
            break;

        case 404:
            status_text = "Not Found";
            break;

        case 500:
            status_text = "Internal Server Error";
            break;

        default:
            return -1;
    }

    char response[4096];

    int length = snprintf(
        response,
        sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status_code,
        status_text,
        strlen(body),
        body
    );

    if (length < 0 || length >= (int)sizeof(response))
    {
        return -1;
    }

    ssize_t sent = send(client_fd, response, length, 0);

    if (sent == -1)
    {
        return -1;
    }

    return 0;
}

int response_send_file(int client_fd, int status_code, const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        return -1;
    }

    fseek(file, 0, SEEK_END);

    long file_size = ftell(file);

    rewind(file);

    if (file_size < 0)
    {
        fclose(file);
        return -1;
    }

    char *body = malloc((size_t)file_size + 1);

    if (body == NULL)
    {
        fclose(file);
        return -1;
    }

    size_t bytes_read = fread(body, 1, (size_t)file_size, file);

    fclose(file);

    body[bytes_read] = '\0';

    int result = response_send(client_fd, status_code, body);

    free(body);

    return result;
}