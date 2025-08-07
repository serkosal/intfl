// #include <iostream>
#ifdef USE_N_CURSES
    #include <ncurses.h>
    #include <cstring>
#else
    #include <iostream>
#endif

#include "Directory.hpp"

int main()
{
    // ncurses.h init
    #ifdef USE_N_CURSES
        setlocale(LC_ALL, "");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE); // enables f1, f2, ... ; and also arrows keys

        printw("Using NCURSES!\n");
    #else 
        std::cout << "using standard library!'n"; 
    #endif
    

    Directory dir(".");

    if (!dir.exists())
    {
        #ifdef USE_N_CURSES
            printw("Directory not found!\n");
            refresh();
            char str[80];
            getstr(str);
            while (strcmp(str, "quit") != 0)
                getstr(str);
            endwin();
        #else
            std::cerr << "Directory not found!\n";
        #endif
        
        return 1;
    }
    
    dir.print();
    #ifdef USE_N_CURSES
        refresh();
        char str[80];
        getstr(str);
        while (strcmp(str, "quit") != 0)
                getstr(str);
        endwin();
    #endif

    return 0;
}
