#include<server.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include<netinet/in.h>
#include<unistd.h>

const char MAGIC[8] = "PATCH_C";

Server* Server_connect(uint16_t port, uint32_t addr) {
    Server* server = malloc(sizeof(Server));
    if(server == nullptr) return nullptr;
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socket_fd < 0) { free(server); return nullptr; }
    server->addr = (struct sockaddr_in){
        AF_INET,
        htons(port),
        htonl(addr)
    };
    int atmpts = 10;
    
    while (connect(server->socket_fd, (struct sockaddr*)&server->addr, sizeof(struct sockaddr_in)) < 0)
    {
        atmpts--;
        if(atmpts < 0) return nullptr;
        write(STDERR_FILENO, "fail\n", 6);
        sleep(1);
    }
    write(STDOUT_FILENO, "connected\n", 11);
    
    write(server->socket_fd, MAGIC, sizeof(uint64_t));


    return server;

}

void Server_disconnect(Server* server) {
    close(server->socket_fd);
    free(server);
}