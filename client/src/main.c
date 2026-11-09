#include<stdint.h>
#include<unistd.h>
#include<server.h>
#include<display.h>


const uint16_t PORT = 8080;
const uint32_t ADDRESS = (10u << 24) | (0u << 16) | (0u << 8) | (124u << 0);

int main(){
    
    
    
    Display* display = Display_init();
    Server* server = Server_connect(PORT, ADDRESS);
    if(server == nullptr) return -1;

    Display_clear(display, 0);
    Display_update(display, 0);
    sleep(1);
    int w1 = Display_new_window(display, 10, 10, 10, 10);
    Display_update(display, w1);
    sleep(2);
    Display_clear(display, w1);
    Display_update(display, w1);
    sleep(10);
    Server_disconnect(server);
    Display_destroy(display);
    

    
    return 0;
}
