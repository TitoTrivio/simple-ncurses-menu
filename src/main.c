#include "main_window.h"

const int kmain_window_height = 15; // lines
const int kmain_window_width  = 40; // columns

WINDOW *main_window;

int main()
{
    // start curses mode
    initscr();

    // don't print every keyboard input
    noecho();

    // disable line buffer but keep control character processing
    cbreak();
    
    // my custom function to create the main window
    create_main_window(main_window, kmain_window_height, kmain_window_width); 

    getch();

    // end curses mode
    endwin();

    return 0;
}

