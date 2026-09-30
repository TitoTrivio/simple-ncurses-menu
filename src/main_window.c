#include "main_window.h"
#include <string.h>

void draw_main_borders(WINDOW *win);
void print_main_header(WINDOW *win);

void create_main_window(WINDOW *win, int height, int width)
{
    int max_y, max_x, start_y, start_x;

    getmaxyx(stdscr, max_y, max_x);

    // draw window in the center of the terminal
    start_y = (max_y / 2) - (height / 2);
    start_x = (max_x / 2) - (width / 2);

    win = newwin(height, width, start_y, start_x);
    refresh();

    // draw borders around the main window
    draw_main_borders(win);
    
    // print header on main window
    print_main_header(win);
}

void draw_main_borders(WINDOW *win)
{
    box(win, 0, 0);
    wrefresh(win);
}

void print_main_header(WINDOW *win)
{
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(win, 1, header_length / 2, "%s", header_text);
    wrefresh(win);
}

