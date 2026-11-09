#include<stdint.h>
#include<server.h>


const uint16_t PORT = 8080;
const uint32_t ADDRESS = (127u << 24) | (0u << 16) | (0u << 8) | (1u << 0);

int main(){
    Server* server = Server_connect(PORT, ADDRESS);
    if(server == nullptr) return -1;
    
    

    Server_disconnect(server);
    return 0;
}