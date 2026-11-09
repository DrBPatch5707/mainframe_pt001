#ifndef __CLIENT_H__
#define __CLIENT_H__

#define _MAGIC "PATCH_S"

//represents the client(data/connection)
typedef struct {
    int client_fd;
} Client;

Client* Client_init(int socket);
void Client_destroy(Client*);





#endif // __CLIENT_H__