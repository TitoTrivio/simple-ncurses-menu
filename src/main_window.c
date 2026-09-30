#include "main_window.h"
#include <string.h>

const char *menu_options[] = {
    "1 - One",
    "2 - Two",
    "3 - Three"
};

void print_menu(WINDOW *win, int start_y, int start_x, size_t index);

WINDOW *create_main_window(int height, int width)
{
    int max_y, max_x, start_y, start_x;

    getmaxyx(stdscr, max_y, max_x);

    // draw window in the center of the terminal
    start_y = (max_y / 2) - (height / 2);
    start_x = (max_x / 2) - (width / 2);
    
    WINDOW *win = newwin(height, width, start_y, start_x);

    // refresh stdscr to show the newly created window
    refresh();

    // draw borders around the main window
    box(win, 0, 0);
    
    // print header on main window
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(win, 1, header_length / 2, "%s", header_text);

    // refresh window to show updates
    wrefresh(win);

    print_menu(win, 3, 1, 0);
    return win;
}

void print_menu(WINDOW *win, int start_y, int start_x, size_t index)
{
   size_t n_options = sizeof(menu_options) / sizeof(char *);

   for (size_t i = 0; i < n_options; ++i)
   {
       if (index == i)
        {
            wattron(win, A_REVERSE);
            mvwprintw(win, i + start_y, start_x, "%s", menu_options[i]);
            wattroff(win, A_REVERSE);
        }
       else
           mvwprintw(win, i + start_y, start_x, "%s", menu_options[i]);
   }

   wrefresh(win);
}

void destroy_main_window(WINDOW *win)
{
    int max_y, max_x;

    getmaxyx(win, max_y, max_x);

    for (int i = 0; i < max_y; ++i)
        for (int j = 0; j < max_x; ++j)
            mvwaddch(win, i, j, ' ');

    wrefresh(win);
    delwin(win);
}

