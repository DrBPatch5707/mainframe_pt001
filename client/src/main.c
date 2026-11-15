
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include<stdint.h>
#include<unistd.h>
#include<server.h>
#include<display.h>
#include<stdbool.h>
#include<string.h>
#include<helper.h>
#include<dispatch.h>
#include<stdbool.h>


const uint16_t PORT = 8080;
const uint32_t ADDRESS = (10u << 24) | (0u << 16) | (0u << 8) | (124u << 0);





int main(){
    
    Display* display = Display_init();
    Server* server = Server_connect(PORT, ADDRESS);
    if(server == nullptr) { Display_destroy(display); return -1; }
    Display_clear(display, 0);
    Display_update(display, 0);
    DispatchArgs args;
    dispatch(display, &args);
    Display_update(display, 0);
    Server_disconnect(server);
    Display_destroy(display);

    
    return 0;
}




