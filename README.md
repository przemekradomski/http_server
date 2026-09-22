# HTTP Server (C)
 
A simple HTTP server written in plain C, built on BSD sockets (`socket`, `bind`, `listen`, `accept`) and `select()` to handle multiple events at once (client connections + console commands).
 
## Features
 
- Listens on port `8080` (constant defined in `server.h`).
- Parses the first line of an HTTP request (method, path, version) in `request.c`.
- Handles a single route:
  - `GET /` → returns `public/index.html` with status `200`.
  - any other path → returns `public/404.html` with status `404`.
- Sends proper HTTP headers (`Content-Type`, `Content-Length`, `Connection: close`).
- Runtime control from the terminal: typing `stop` or `exit` shuts the server down.
## Project structure
 
```
http_server/
├── src/
│   ├── main.c          # main loop, select() on stdin + server socket
│   ├── server.c/.h     # socket creation, bind, listen, accept
│   ├── request.c/.h    # HTTP request line parsing
│   ├── response.c/.h   # building and sending HTTP responses, sending files
│   ├── router.c/.h     # simple routing (currently unused in main.c)
│   └── http.c/.h       # alternative request parser (currently unused, contains a bug)
├── public/
│   ├── index.html      # page returned for "/"
│   └── 404.html        # 404 error page
├── tests/              # empty directory, ready for tests
└── makefile            # currently empty
```
 
## Building
 
The `makefile` in this repo is empty, so for now compile manually with `gcc`:
 
```bash
gcc -Wall -Wextra -o server src/main.c src/server.c src/request.c src/response.c
```
 
`router.c` and `http.c` are not included in the build because they're not used in `main.c`, and `http.c` won't compile as it currently stands (see "Known issues").
 
## Running
 
```bash
./server
```
 
The server prints `Server listening on port 8080` and waits for connections. Test it with:
 
```bash
curl http://localhost:8080/
curl http://localhost:8080/anything
```
 
To stop the server: type `stop` or `exit` in the same terminal and press Enter.
 
## Known issues / TODO
 
- `makefile` is empty, there are no build rules yet.
- `http.c` references a `buffer` variable that doesn't exist in the function signature (should be `request_str`) — it won't compile as is.
- `router.c` and `request.c`/`http.c` duplicate the same parsing logic (two nearly identical structs: `HttpRequest` and `HTTPRequest`) — needs consolidating.
- Only `GET /` is handled, the routing logic in `router.c` isn't wired into `main.c` yet.
- The server handles one connection at a time (no threading / connection pool).
- The `tests/` directory is empty — no unit tests yet.
## Requirements
 
- A C compiler (e.g. `gcc`) supporting C99 or newer.
- A POSIX-compliant system (uses `sys/socket.h`, `netinet/in.h`, `arpa/inet.h`, `unistd.h`).