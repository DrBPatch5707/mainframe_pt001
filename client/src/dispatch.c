#include "stb_ds.h"
#include<stdint.h>
#include<unistd.h>
#include<helper.h>
#include<dispatch.h>
#include<display.h>
#include<stdbool.h>
#include<string.h>



typedef struct DispatchEntry{
    char* key;
    DispatchFunc value;
};

DispatchEntry* init_dispatch_hm() {
    DispatchEntry* de = NULL;
    sh_new_arena(de);
    shdefault(de, defaultDispatch);
    shput(de, "exit", exitDispatch);
    shput(de, "users", usersDispatch);
    //others
    return de;
}


int defaultDispatch(DispatchArgs*) {
    return -1;
}

int exitDispatch(DispatchArgs*) {
    return -2;
}

int usersDispatch(DispatchArgs*) {
    
    return 0;
}


int dispatch(Display* dsp, DispatchArgs* args) {
    DispatchEntry* de = init_dispatch_hm();
    
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
DispatchFunc ds;
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
            if(ds != defaultDispatch) _exit = ((*ds)(args) == -2);
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
    shfree(de);
    return 0;
}