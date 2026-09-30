#include "main_window.h"
#include <string.h>

const char *menu_options[] = {
    "1 - One",
    "2 - Two",
    "3 - Three"
};

size_t n_options = sizeof(menu_options) / sizeof(char *);

void print_menu(MainWindow *mw, int start_y, int start_x, size_t index);

void main_window_initialize(MainWindow *mw, WINDOW *parent_window, int height, int width)
{
    mw->window = NULL;
    mw->parent_window = parent_window;
    mw->height = height;
    mw->width = width;
    
    int parent_max_y, parent_max_x, start_y, start_x;

    getmaxyx(parent_window, parent_max_y, parent_max_x);

    // draw window in the center of the terminal
    start_y = (parent_max_y / 2) - (height / 2);
    start_x = (parent_max_x / 2) - (width / 2);
    
    mw->window = newwin(height, width, start_y, start_x);

    // refresh stdscr to show the newly created window
    wrefresh(parent_window);

    // enable reading function keys
    keypad(mw->window, true);

    // draw borders around the main window
    box(mw->window, 0, 0);
    
    // print header on main window
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(mw->window, 1, header_length / 2, "%s", header_text);

    // temporary message
    mvwprintw(mw->window, height - 2, 1, "%s", "Move with arrows. Press \'q\' to exit.");

    // refresh window to show updates
    wrefresh(mw->window);
}

void main_window_loop(MainWindow *mw)
{
    int c = '\0';
    size_t menu_index = 0;

    while (c != 'q')
    {
        print_menu(mw, 3, 1, menu_index);

        c = wgetch(mw->window);

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

void main_window_finalize(MainWindow *mw)
{
    if (mw->window)
    {
        for (int i = 0; i < mw->height; ++i)
            for (int j = 0; j < mw->width; ++j)
                mvwaddch(mw->window, i, j, ' ');

        wrefresh(mw->window);
        delwin(mw->window);
    }

    mw->window = NULL;
    mw->parent_window = NULL;
    mw->height = 0;
    mw->width = 0;
}

void print_menu(MainWindow *mw, int start_y, int start_x, size_t index)
{
   for (size_t i = 0; i < n_options; ++i)
   {
       if (index == i)
        {
            wattron(mw->window, A_REVERSE);
            mvwprintw(mw->window, i + start_y, start_x, "%s", menu_options[i]);
            wattroff(mw->window, A_REVERSE);
        }
       else
           mvwprintw(mw->window, i + start_y, start_x, "%s", menu_options[i]);
   }

   wrefresh(mw->window);
}

