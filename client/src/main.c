
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
typedef enum Dispatch{
UNKNOWN_TOOL,
EXIT
}Dispatch;
typedef struct {
    char* key;
    Dispatch value;
}DispatchEntry;

DispatchEntry* init_hm() {
    DispatchEntry* de = NULL;
    sh_new_arena(de);
    shdefault(de, UNKNOWN_TOOL);
    shput(de, "exit", EXIT);
    //others
    return de;
}


Dispatch dispatch(Display*);

int main(){
    
    Display* display = Display_init();
    Server* server = Server_connect(PORT, ADDRESS);
    if(server == nullptr) { Display_destroy(display); return -1; }
    Display_clear(display, 0);
    Display_update(display, 0);
    Dispatch ds = dispatch(display);
    Display_update(display, 0);
    Server_disconnect(server);
    Display_destroy(display);

    
    return 0;
}




Dispatch dispatch(Display* dsp) {
    DispatchEntry* de = init_hm();
    
    int W,H;
    Display_getsize_Scr(&W, &H);
    int x, y;
    const int CW = 20, CH = 3;
    center(&x, &y, W, H, CW, CH);
    int inwin = Display_new_window(dsp, CH, CW, y, x);
    Display_draw_border(dsp, inwin);
    int infowin = Display_new_window(dsp, CH, CW, y + (CH/2), x - (CW - 4));
    Display_write(dsp, infowin, "Enter dispatch:", 16);
    Display_update(dsp, infowin);
    Display_move_cursor(dsp,inwin, 2, 1);
    

bool _exit = false;
Special_char sc = UNKNOWN;
Dispatch ds;
while (!_exit)
{
    Display_update(dsp, inwin);
    char ch = Display_get_char(dsp, inwin, &sc);
    if(ch != '\0') {
        Display_write_ch(dsp, inwin, ch);
    } else {
        switch (sc)
        {
        case ENTER:{
            char d[6] = {'\0'};
            Display_get_buffer(dsp, inwin, d, 2, 1, 5, 1, 1, 2, 8); ///TODO: verify return //magic numbers bad deal with later
            remove_char(d, 6, ' ');
            ds = shget(de, d);
            if(ds != UNKNOWN_TOOL) _exit = true;
            break;}
        case BACKSPACE:
            Display_Backspace(dsp, inwin);
        default:
            break;
        }
    }
}



    Display_delete_window(dsp, infowin);
    Display_delete_window(dsp, inwin);
    return ds;
}