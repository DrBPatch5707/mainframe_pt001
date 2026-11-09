#include <Client.h>
#include<helper.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdint.h>
#include<string.h>
#include<fcntl.h>


Client* Client_init(int socket) {
    const char CLIENT_MAGIC[8] = "PATCH_C";
    Client* client = (Client*)malloc(sizeof(Client));
    if(client == nullptr) return nullptr;
    write(STDOUT_FILENO, "Accepting clients...\n", 22);
    client->client_fd = accept(socket, 0, 0);
    //verify fd
    if(!verify_fd(client->client_fd, "client socket accept")) { free(client); return nullptr;} //flag that states "DO NOT USE"
    fcntl(client->client_fd, F_SETFL, O_NONBLOCK); //REPLACES FLAGS!!! DON'T GET CONFUSED LATER
    //verify client
    char buf[256] = {0};
    int ammt_read = 0; short int atmps = 10;
    do
    {
        int cr = read(client->client_fd, &buf[ammt_read], sizeof(CLIENT_MAGIC) - ammt_read);
        if(cr > 0) ammt_read += cr;
        atmps--;
        if(atmps < 0){Client_destroy(client); return nullptr; }
        if(ammt_read < sizeof(CLIENT_MAGIC)) sleep(2);
    } while (ammt_read < sizeof(CLIENT_MAGIC));

    //no api security now ill implement later
    
    if (memcmp(buf, CLIENT_MAGIC, sizeof(CLIENT_MAGIC)) != 0) {
        write(STDOUT_FILENO, "error: invalid handshake\n", 26);
        Client_destroy(client); return nullptr;
    } else write(STDOUT_FILENO, "handshake validated\n", 20);
    write(STDOUT_FILENO, buf, ammt_read);
    write(STDOUT_FILENO, "\n", 2);
    return client;

}
void Client_destroy(Client* c) {
    if(c == nullptr) return;
    close(c->client_fd);
    free(c);
}