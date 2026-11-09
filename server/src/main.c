#define _POSIX_C_SOURCE 200809L
#include <sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<stdbool.h>
#include<Client.h>
#include<helper.h>
#include<signal.h>

const uint16_t PORT = 8080;
volatile sig_atomic_t exit_please = false;

static void sigint_handler(int signum) {
    (void)signum;
    exit_please = true;
}

int main(){
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGINT, &sa, NULL) < 0) {
        write(STDERR_FILENO, "sigaction failed\n", 18);
        return -1;
    }
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
    
    do
    {
        Client* c = Client_init(socket_fd);
        if(c == nullptr) break;
        sleep(2); // change later
        Client_destroy(c);
    } while (!exit_please);
    

    if(close(socket_fd) == 0) write(STDOUT_FILENO, "socket closed\n", 15);
    else { write(STDOUT_FILENO, "socket did not close\n", 22); return -1; }


    return 0;
}
