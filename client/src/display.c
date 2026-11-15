#include<display.h>
#include<curses.h>
#include<locale.h>
#include<stdlib.h>
#include<stb_ds.h>

struct Display {
    WINDOW** windows;
    int max_windows;
    int amt_windows;
    int* recyclable_windows;
    SCREEN* screen;
};


Display* Display_init() {
    //TODO: Implement proper checks for all of this.
    setlocale(LC_ALL, "");
    Display* display = (Display*)malloc(sizeof(Display));
    display->amt_windows = 0;
    display->screen = newterm(NULL, stdout, stdin);
    display->windows = malloc(10 * sizeof(WINDOW*)); display->max_windows = 10;
    set_term(display->screen);
    display->windows[0] = stdscr; display->amt_windows++;

    cbreak();
    noecho();
    nodelay(display->windows[0], TRUE);
    keypad(display->windows[0], TRUE); //we'll start with the initial window
    wrefresh(display->windows[0]);
    display->recyclable_windows = NULL;
    return display;
}

void Display_clear(Display* dsp, int win) {
    if(win >= 0 && win < dsp->amt_windows) wclear(dsp->windows[win]);
}

void Display_destroy(Display* obj) {
    // do not delete stdscr
    for (int i = 1; i < obj->amt_windows; i++) delwin(obj->windows[i]);
    endwin();
    delscreen(obj->screen);
    free(obj->windows);
    free(obj);
}

void Display_getsize_win(Display* dsp, int win, int* w, int* h) { getmaxyx(dsp->windows[win], *h, *w); }
void Display_getsize_Scr(int* w, int* h) { *w = COLS; *h = LINES; }

int Display_get_buffer(Display* dsp, int win, char* dest, int x, int y, int size , int h_min, int h_max, int w_min, int w_max) {
    int i = 0;
    int yi = y;
    for (int xi = x; i < size; xi++) {
        if(xi > w_max) { yi++; xi = w_min;}
        if(yi >h_max) yi = h_min;
        dest[i] = (char)((mvwinch(dsp->windows[win], yi, xi)) & A_CHARTEXT);
        i++;
    }
    return i;
}

char Display_get_char(Display* dsp, int win, Special_char* sc) {
    *sc = UNKNOWN;
    int ch = wgetch(dsp->windows[win]);
    if(ch >= 32 && ch <= 126) return (char)ch;
    switch (ch)// DON'T FORGET TO DEREFERANCE SC!!!
    {
    case ERR:
        *sc = NOINPUT;
        break;
    
    case KEY_ENTER:
        *sc = ENTER;
        break;
    
    default:
        *sc = UNKNOWN;
        break;
    }
    return '\0';
}



void Display_draw_border(Display* dsp, int win) { box(dsp->windows[win], 0, 0); }



void Display_update(Display* dsp, int win) { if(win >= 0 && win < dsp->amt_windows) wrefresh(dsp->windows[win]); }


int Display_new_window(Display* dsp, int h, int w, int y, int x) {
    //TODO: Perform checks for all this, especially the reallocation.
    int newindex = -1;
    if(arrlen(dsp->recyclable_windows) > 0) newindex = arrpop(dsp->recyclable_windows);
    else if(dsp->amt_windows + 1 > dsp->max_windows) {
        dsp->windows = realloc(dsp->windows, (sizeof(WINDOW*) * (dsp->max_windows + 10)));
        dsp->max_windows += 10;
    }
    if(newindex == -1) { newindex = dsp->amt_windows; dsp->amt_windows++; }
    dsp->windows[newindex] = newwin(h, w, y, x);
    nodelay(dsp->windows[newindex], TRUE);
    return newindex;
}

void Display_delete_window(Display*dsp, int win) {
    if(dsp->windows[win] == NULL) return;
    delwin(dsp->windows[win]);// TODO: add return value check
    arrput(dsp->recyclable_windows, win);
    dsp->windows[win] = NULL;
}

void Display_move_cursor(Display* dsp, int win, int x, int y) {
    // TODO: add return value checks
    wmove(dsp->windows[win], y, x);
}