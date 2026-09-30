#include <ncurses.h>
#include <string.h>

const int kmain_window_height = 15; // lines
const int kmain_window_width  = 40; // columns

WINDOW *main_window;

void create_main_window();
void draw_main_borders();
void print_main_header();

int main()
{
    // start curses mode
    initscr();

    // don't print every keyboard input
    noecho();

    // disable line buffer but keep control character processing
    cbreak();
    
    // create the main window
    create_main_window(); 

    // draw borders around the main window
    draw_main_borders();
    
    // print header on main window
    print_main_header();

    getch();

    // end curses mode
    endwin();

    return 0;
}

void create_main_window()
{
    int max_y, max_x, start_y, start_x;

    getmaxyx(stdscr, max_y, max_x);

    // draw window in the center of the terminal
    start_y = (max_y / 2) - (kmain_window_height / 2);
    start_x = (max_x / 2) - (kmain_window_width / 2);

    main_window = newwin(kmain_window_height, kmain_window_width, start_y, start_x);
    refresh();
}

void draw_main_borders()
{
    box(main_window, 0, 0);
    wrefresh(main_window);
}

void print_main_header()
{
    const char* header_text = "SIMPLE NCURSES MENU";
    size_t header_length = strlen(header_text);

    mvwprintw(main_window, 1, header_length / 2, "%s", header_text);
    wrefresh(main_window);
}

