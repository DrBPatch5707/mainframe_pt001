
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


/*
 * DESIGN CHANGE: Terminal UI -> Dispatch UI
 *
 * Decided to replace the terminal-style interface with a simpler
 * ncurses UI containing a dedicated dispatch input field.
 *
 * Since dispatch codes are limited to 5 characters, implementing
 * a full terminal with cursor movement, wrapping, and text editing
 * adds unnecessary complexity.
 *
 * The new interface will collect a dispatch code and pass it to
 * the dispatch system to determine which tool to launch.
 *
 * Keep the reusable ncurses display, window management, and input
 * abstractions. Only remove the terminal-specific functionality.
 *
 * IMPORTANT: The original terminal implementation was committed
 * to Git before removal. It can be recovered or branched from
 * later if needed.
 */
Dispatch dispatch(Display* dsp) {
    
}