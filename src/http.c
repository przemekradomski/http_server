#include "http.h"

#include <stdio.h>
#include <string.h>

int http_parse_request(const char *request_str, HTTPRequest *request){

    if(buffer == NULL || request == NULL){
        return -1;
    }

    int result = sscanf(
        buffer, "%15s %255s %15s",
        request->method,
        request->path,
        request->version
    );

    if(result != 3){
        return -1;
    }

    return 0;

}