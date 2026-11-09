#ifndef __DISPLAY_H__
#define __DISPLAY_H__

typedef struct {
    /* data */
}Display;

Display* Display_init();
void Draw_terminal();
void Display_destroy();

#endif // __DISPLAY_H__