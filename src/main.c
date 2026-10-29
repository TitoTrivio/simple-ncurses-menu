#include <ncurses/ncurses.h>
#include <string.h>

void print_menu(WINDOW *window, int const start_y, int const start_x, size_t const index);
void window_loop(WINDOW *window);

int main()
{
    // Initialize curses mode

    initscr();

    // Configuration

    noecho();
    cbreak();
    curs_set(0);

    // Draw window in the center of the terminal

    int const height = 15; // lines
    int const width  = 45; // columns
    
    int terminal_max_y, terminal_max_x, window_start_y, window_start_x;

    getmaxyx(stdscr, terminal_max_y, terminal_max_x);

    window_start_y = (terminal_max_y / 2) - (height / 2);
    window_start_x = (terminal_max_x / 2) - (width / 2);
    
    WINDOW *window = newwin(height, width, window_start_y, window_start_x);

    // Refresh stdscr to show the window
    
    refresh();

    // Enable function keys (like arrow keys) on window

    keypad(window, true);

    // Draw simple borders around the window
    
    box(window, 0, 0);
    
    // Print header and instructions
    
    mvwprintw(window, 1, 1, "%s", "SIMPLE NCURSES MENU");

    mvwprintw(window, 3, 1, "%s", "Move with arrows. Press ENTER to select.");

    // Refresh window to show updates

    wrefresh(window);

    // Execute window loop

    window_loop(window);

    // End curses mode

    endwin();

    return 0;
}

char const *menu_options[] = {
    "- One",
    "- Two",
    "- Exit"
};

size_t const n_options = sizeof(menu_options) / sizeof(char *);

void print_menu(WINDOW *window, int const start_y, int const start_x, size_t const index)
{
    for (size_t i = 0; i < n_options; ++i)
    {
        if (index == i)
        {
            wattron(window, A_REVERSE);
            mvwprintw(window, i + start_y, start_x, "%s", menu_options[i]);
            wattroff(window, A_REVERSE);
        }
        else
            mvwprintw(window, i + start_y, start_x, "%s", menu_options[i]);
    }

    wrefresh(window);
}

void window_loop(WINDOW *window)
{
    int c = '\0';
    size_t menu_index = 0;

    while (true)
    {
        print_menu(window, 5, 1, menu_index);

        c = wgetch(window);

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

