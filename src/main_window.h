#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <ncurses.h>

void create_main_window(WINDOW *win, int height, int width);
void draw_main_borders(WINDOW *win);
void print_main_header(WINDOW *win);

#endif

