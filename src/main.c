#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "server.h"
#include "request.h"
#include "response.h"

int main(void)
{
    int server_fd = server_create();

    if (server_fd == -1)
    {
        return 1;
    }

    printf("Type 'stop' or 'exit' to stop the server.\n");

    while (1)
    {
        fd_set read_fds;

        FD_ZERO(&read_fds);

        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(server_fd, &read_fds);

        int max_fd = server_fd;

        if (STDIN_FILENO > max_fd)
        {
            max_fd = STDIN_FILENO;
        }

        int result = select(
            max_fd + 1,
            &read_fds,
            NULL,
            NULL,
            NULL
        );

        if (result == -1)
        {
            perror("select");
            break;
        }


        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            char command[128];

            if (fgets(command, sizeof(command), stdin) == NULL)
            {
                break;
            }

            command[strcspn(command, "\n")] = '\0';

            if (strcmp(command, "stop") == 0 || strcmp(command, "exit") == 0)
            {
                printf("Shutting down server...\n");
                printf("bye \n");
                break;
            }

            printf("Unknown command: %s\n", command);
        }

        if (FD_ISSET(server_fd, &read_fds))
        {
            int client_fd = server_accept(server_fd);

            if (client_fd == -1)
            {
                continue;
            }

            char buffer[4096];

            int bytes_received = recv(
                client_fd,
                buffer,
                sizeof(buffer) - 1,
                0
            );

            if (bytes_received > 0)
            {
                buffer[bytes_received] = '\0';

                HttpRequest request;

                if (request_parse(buffer, &request) == 0)
                {
                    printf(
                        "Method: %s | Path: %s | Version: %s\n",
                        request.method,
                        request.path,
                        request.version
                    );

                    if (strcmp(request.path, "/") == 0)
                    {
                        response_send_file(
                            client_fd,
                            200,
                            "public/index.html"
                        );
                    }
                    else
                    {
                        response_send_file(
                            client_fd,
                            404,
                            "public/404.html"
                        );
                    }
                }
            }

            close(client_fd);
        }
    }

    close(server_fd);

    printf("Server stopped.\n");

    return 0;
}