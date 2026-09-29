#include <ncurses.h>

int main()
{
    initscr();
    noecho();
    cbreak();

    printw("Hello, world!");

    getch();

    endwin();

    return 0;
}

