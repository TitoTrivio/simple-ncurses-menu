#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <ncurses.h>

typedef struct MainWindow
{
    WINDOW *window;
    int height;
    int width;
} MainWindow;

void main_window_initialize(MainWindow *mw, int height, int width);
void main_window_loop(MainWindow *mw);
void main_window_finalize(MainWindow *mw);

#endif

