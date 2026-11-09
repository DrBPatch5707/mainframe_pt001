#include <sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<arpa/inet.h>

#include<Client.h>
#include<helper.h>

const uint16_t PORT = 8080;

int main(){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!verify_fd(socket_fd, "socket")) return -1;
    write(STDOUT_FILENO, "socket opened\n", 15);
    struct sockaddr_in addr = {
        AF_INET,
        htons(PORT),
        0
    };
    if (!verify_fd(bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)), "socket bind")) {
        close(socket_fd);
        return -1;
    }
    write(STDOUT_FILENO, "socket bound\n", 14);
    if (!verify_fd(listen(socket_fd, 5), "socket listen")) {
        close(socket_fd);
        return -1;
    }
    write(STDOUT_FILENO, "socket listening...\n", 21);
    Client* c = Client_init(socket_fd);
    if(c == nullptr) {close(socket_fd); return -1; }


    Client_destroy(c);
    close(socket_fd);
    return 0;
}
