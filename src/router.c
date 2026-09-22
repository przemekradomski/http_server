#include "router.h"

#include <string.h>

int router_handle(const HttpRequest *request)
{
    if (request == NULL)
    {
        return -1;
    }

    if (strcmp(request->path, "/") == 0)
    {
        return 0;
    }

    if (strcmp(request->path, "/about") == 0)
    {
        return 0;
    }

    return -1;
}