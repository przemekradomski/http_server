#include "request.h"

#include <stdio.h>

int request_parse(const char *buffer, HttpRequest *request)
{
    if (buffer == NULL || request == NULL)
    {
        return -1;
    }

    int result = sscanf(
        buffer,
        "%15s %255s %15s",
        request->method,
        request->path,
        request->version
    );

    if (result != 3)
    {
        return -1;
    }

    return 0;
}