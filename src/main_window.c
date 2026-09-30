#include "main_window.h"
#include <string.h>

const char *menu_options[] = {
    "- One",
    "- Two",
    "- Exit"
};

size_t n_options = sizeof(menu_options) / sizeof(char *);

void print_menu(MainWindow *mw, int start_y, int start_x, size_t index);

void main_window_initialize(MainWindow *mw, int height, int width)
{
    mw->window = NULL;
    mw->height = height;
    mw->width = width;
    
    int terminal_max_y, terminal_max_x, start_y, start_x;

    getmaxyx(stdscr, terminal_max_y, terminal_max_x);

    // draw window in the center of the terminal
    start_y = (terminal_max_y / 2) - (height / 2);
    start_x = (terminal_max_x / 2) - (width / 2);
    
    mw->window = newwin(height, width, start_y, start_x);

    // refresh stdscr to show the newly created window
    wrefresh(stdscr);

    // enable reading function keys
    keypad(mw->window, true);

    // draw borders around the main window
    box(mw->window, 0, 0);
    
    // print header on main window
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(mw->window, 1, (width / 2) - (header_length / 2), "%s", header_text);

    // print instructions on main window
    mvwprintw(mw->window, 3, 1, "%s", "Move with arrows. Press ENTER to select.");

    // refresh window to show updates
    wrefresh(mw->window);
}

void main_window_loop(MainWindow *mw)
{
    int c = '\0';
    size_t menu_index = 0;

    while (true)
    {
        print_menu(mw, 5, 1, menu_index);

        c = wgetch(mw->window);

        switch (c)
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

            case '\n':
            case KEY_ENTER:
                switch (menu_index)
                {
                    case 2:
                        return;
                }

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

