
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
    const int win = 0;
    int X_MAX, X_MIN = 2;//TODO: make dynamic later
    int Y_MAX, Y_MIN = 2;//<^
    Display_getsize(dsp, win, &X_MAX, &Y_MAX); Y_MAX -= 2; X_MAX -= 2;
    int cx = X_MIN, cy = Y_MIN;
    bool _exit = false;
    Dispatch dispatch = UNKNOWN_TOOL;
    Special_char sc = UNKNOWN;
    Display_draw_terminal(dsp, win);
    Display_move_cursor(dsp, win, cx, cy);
    Display_update(dsp, win);
    
    while (!_exit)
    {
        char ch = Display_get_char(dsp, win, &sc);
        if(ch == '\0') {
            switch (sc)
            {
            case ENTER:
                char d[6] = {'\0'};
                Display_get_buffer(dsp, win, d, X_MIN, Y_MIN, 5, Y_MIN, Y_MAX, X_MIN, X_MAX); ///TODO: verify return
                dispatch = shget(de, d);
                break;
            
            default:
                break;
            }
        }else {
            cx++;
        }
        if(dispatch != UNKNOWN_TOOL) _exit = true;

        if(cx >= X_MAX) cy++;
        else if (cx <= X_MIN) cy--;
        cx = wrap(cx, X_MAX, X_MIN);
        cy = wrap(cy, Y_MAX, Y_MIN);
        Display_move_cursor(dsp, win, cx, cy); //wasteful
        Display_update(dsp, win);
    }
    
    shfree(de);
    return dispatch;
}