
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include<stdint.h>
#include<unistd.h>
#include<server.h>
#include<display.h>
#include<stdbool.h>
#include<string.h>
#include<helper.h>



const uint16_t PORT = 8080;
const uint32_t ADDRESS = (10u << 24) | (0u << 16) | (0u << 8) | (124u << 0);
typedef enum {
UNKNOWN_TOOL,
EXIT
}Dispatch;
typedef struct {
    char* key;
    Dispatch value;
}DispatchEntry;

void init_hm(DispatchEntry* de) {
    sh_new_arena(de);
    shdefault(de, UNKNOWN_TOOL);
    shput(de, "exit", EXIT);
    //others
}


Dispatch dispatch(Display*);

int main(){
    
    Display* display = Display_init();
    Server* server = Server_connect(PORT, ADDRESS);
    if(server == nullptr) { Display_destroy(display); return -1; }

    Display_clear(display, 0);
    Display_update(display, 0);
    sleep(1);
    Dispatch ds = dispatch(display);
    Display_update(display, 0);
    sleep(10);
    Server_disconnect(server);
    Display_destroy(display);

    
    return 0;
}




Dispatch dispatch(Display* dsp) {
    DispatchEntry* de = NULL;
    init_hm(de);
    int W,H;
    Display_getsize_Scr(W, H);
    int win = Display_new_window(dsp, H, W, 0, 0);
    Display_draw_border(dsp, win);







    
}