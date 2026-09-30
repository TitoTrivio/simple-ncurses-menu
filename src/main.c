#include "main_window.h"

int main()
{
    // start curses mode
    initscr();

    // don't print every keyboard input
    noecho();

    // disable line buffer but keep control character processing
    cbreak();

    // turn cursor invisible
    curs_set(0);
    
    // create main window with custom function
    const int kmain_window_height = 15; // lines
    const int kmain_window_width  = 40; // columns

    WINDOW *main_window = create_main_window(kmain_window_height, kmain_window_width); 

    getch();

    destroy_main_window(main_window);

    // end curses mode
    endwin();

    return 0;
}

