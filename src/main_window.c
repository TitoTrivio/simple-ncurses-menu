#include "main_window.h"
#include <string.h>

const char *menu_options[] = {
    "1 - One",
    "2 - Two",
    "3 - Three"
};

size_t n_options = sizeof(menu_options) / sizeof(char *);

void print_menu(WINDOW *win, int start_y, int start_x, size_t index);

WINDOW *create_main_window(int height, int width)
{
    int terminal_max_y, terminal_max_x, start_y, start_x;

    getmaxyx(stdscr, terminal_max_y, terminal_max_x);

    // draw window in the center of the terminal
    start_y = (terminal_max_y / 2) - (height / 2);
    start_x = (terminal_max_x / 2) - (width / 2);
    
    WINDOW *win = newwin(height, width, start_y, start_x);

    // refresh stdscr to show the newly created window
    refresh();

    // enable reading function keys
    keypad(win, true);

    // draw borders around the main window
    box(win, 0, 0);
    
    // print header on main window
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(win, 1, header_length / 2, "%s", header_text);

    int max_y, max_x;

    getmaxyx(win, max_y, max_x);

    // temporary message
    mvwprintw(win, max_y - 2, 1, "%s", "Move with arrows. Press \'q\' to exit.");

    // refresh window to show updates
    wrefresh(win);

    return win;
}

void main_window_loop(WINDOW *win)
{
    int c = '\0';
    size_t menu_index = 0;

    while (c != 'q')
    {
        print_menu(win, 3, 1, menu_index);

        c = wgetch(win);

        switch(c)
        {
            case KEY_UP:
                if (menu_index == 0)
                    menu_index = n_options - 1;
                else
                    --menu_index;
                break;
            case KEY_DOWN:
                if (menu_index == n_options - 1)
                    menu_index = 0;
                else
                    ++menu_index;
                break;
        }
    }
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

void print_menu(WINDOW *win, int start_y, int start_x, size_t index)
{
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

