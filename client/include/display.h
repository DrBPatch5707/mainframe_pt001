#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <curses.h>




typedef struct Display Display;

typedef enum Special_char{
    UNKNOWN = -2,
    NOINPUT = -1,
    ARROW_UP = 1,
    ENTER = 0,
    ARROW_DOWN = 2,
    ARROW_RIGHT = 3,
    ARROW_LEFT = 4,
    
}Special_char;

Display* Display_init();
void Display_draw_terminal(Display*, int win);
void Display_destroy(Display*);
void Display_clear(Display*, int win);
int Display_new_window(Display*, int h, int w, int y, int x);
void Display_update(Display*, int win);
char Display_get_char(Display* dsp, int win, Special_char* sc);
void Display_move_cursor(Display*, int win, int x, int y);


void Display_getsize(Display* dsp, int win, int* w, int* h);


/**
 * @brief Copies characters from an ncurses window into a buffer.
 *
 * Reads up to `size` characters starting at (x, y), wrapping
 * horizontally and vertically within the specified bounds.
 *
 * @warning By calling this function, the caller certifies that
 * the destination buffer has sufficient capacity for `size` characters.
 * The function does not validate the destination buffer's capacity.
 *
 * @param dsp Display instance.
 * @param win Window index.
 * @param dest Destination buffer.
 * @param x, y Starting coordinates.
 * @param size Number of characters to copy.
 * @param h_min, h_max Vertical bounds (inclusive).
 * @param w_min, w_max Horizontal bounds (inclusive).
 * @return Number of characters copied.
 *
 * @note Does not null-terminate the destination buffer.
 * (this documentation was AI generated)
 */
int Display_get_buffer(Display* dsp, int win, char* dest, int x, int y, int size , int h_min, int h_max, int w_min, int w_max);

#endif // __DISPLAY_H__
