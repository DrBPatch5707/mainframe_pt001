#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <curses.h>




typedef struct Display Display;

Display* Display_init();
void Draw_terminal(Display*);
void Display_destroy(Display*);
void Display_clear(Display*, int win);
int Display_new_window(Display*, int h, int w, int y, int x);
void Display_update(Display*, int win);

#endif // __DISPLAY_H__
