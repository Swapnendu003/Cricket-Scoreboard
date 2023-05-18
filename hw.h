#include <ncurses.h>

int g_choice;  

void style() 
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    int height, width;
    getmaxyx(stdscr, height, width);
    int menuHeight = 5;
    int menuWidth = 40;
    int menuStartY = (height - menuHeight) / 2;
    int menuStartX = (width - menuWidth) / 2;


    WINDOW* mainwin = newwin(menuHeight, menuWidth, menuStartY, menuStartX);
    box(mainwin, 0, 0);
    refresh();
    wrefresh(mainwin);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_YELLOW);
    wbkgd(mainwin, COLOR_PAIR(1) | A_BOLD);


    wattron(mainwin, A_BOLD);
    mvwprintw(mainwin, 1, 1, "1. Enter 1 for new scorecard");
    mvwprintw(mainwin, 2, 1, "2. Enter 2 for view scorecard");
    mvwprintw(mainwin, 3, 1, "3. Enter 3 for exit");
    wattroff(mainwin, A_BOLD);
    wrefresh(mainwin);

   
    g_choice = wgetch(mainwin);

  
    delwin(mainwin);
    endwin();
}
