// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

#ifdef USE_N_CURSES
    #include <ncurses.h>
    #include <cstring>
    #include "Colors.hpp"
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
        // cbreak();
        // noecho();
        //keypad(stdscr, TRUE); // enables f1, f2, ... ; and also arrows keys

        NcursesColors::init();
        if (!NcursesColors::isColors())
            printw("Colors are unsupported. Running without them!\n");
    #else
        std::cout << "Running without NCurses, colors are unsupported!\n";
    #endif
    

    Directory dir(".");

    if (!dir.exists())
    {
        #ifdef USE_N_CURSES
            NcursesColors::ERROR.on();
                printw("Directory not found!\n");
            NcursesColors::ERROR.off();
            refresh();
        #else
            std::cerr << "Directory not found!\n";
        #endif
    }
    
    dir.print();
    #ifdef USE_N_CURSES
        refresh();
        char str[80];
        getstr(str);
        while (strcmp(str, "quit") != 0)
        {
            if (strcmp(str, "redraw") == 0)
            {
                clear();
                dir.print();
                refresh();
            }
            else if (strcmp(str, "help") == 0)
            {
                NcursesColors::NOTICE.on();
                    printw("quit\n");
                    printw("redraw\n");
                NcursesColors::NOTICE.off();
                refresh();
            }
            else
            {
                NcursesColors::ERROR.on();
                    printw("Unrecognized command!\nType help to see commands list\n");
                NcursesColors::ERROR.off();
                refresh();
            }
            getstr(str);
        }
        endwin();
    #endif

    return 0;
}
