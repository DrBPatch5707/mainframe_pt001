#include<display.h>
#include<curses.h>
#include<locale.h>
#include<stdlib.h>

struct Display {
    WINDOW** windows;
    int max_windows;
    int amt_windows;
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
    keypad(display->windows[0], TRUE); //we'll start with the initial window
    wrefresh(display->windows[0]);
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


void Display_update(Display* dsp, int win) { if(win >= 0 && win < dsp->amt_windows) wrefresh(dsp->windows[win]); }


int Display_new_window(Display* dsp, int h, int w, int y, int x) {
    //TODO: Perform checks for all this, especially the reallocation.
    if(dsp->amt_windows + 1 > dsp->max_windows) {
        dsp->windows = realloc(dsp->windows, (sizeof(WINDOW*) * (dsp->max_windows + 10)));
        dsp->max_windows += 10;
    }
    dsp->windows[dsp->amt_windows] = newwin(h, w, y, x);
    dsp->amt_windows++;
    return dsp->amt_windows - 1;
}