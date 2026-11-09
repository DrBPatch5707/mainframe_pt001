#ifndef __SERVER_H__
#define __SERVER_H__
#include <stdint.h>
#include <sys/socket.h>
#include<netinet/in.h>

extern const char MAGIC[8];

typedef struct {
    
    struct sockaddr_in addr;
    int socket_fd;
} Server;


Server* Server_connect(uint16_t port, uint32_t addr);
void Server_disconnect(Server*);

#endif // __SERVER_H__