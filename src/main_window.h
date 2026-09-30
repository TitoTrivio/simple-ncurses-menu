#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <ncurses.h>

WINDOW *create_main_window(int height, int width);
void destroy_main_window(WINDOW *win);

#endif

