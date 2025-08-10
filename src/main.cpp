// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

#define USE_N_CURSES
#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include <cstring>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

#include "Directory.hpp"
#include "MainLoop.hpp"

int main()
{
    // ncurses.h init
    #ifdef USE_N_CURSES

        setlocale(LC_ALL, "en_US.UTF-8");
        initscr();
        // cbreak(); /* Line buffering disabled. pass on everything */
        noecho();

        int y, x;
        getmaxyx(stdscr, y, x);

        WINDOW* mainWin = newwin(y - 10, x, 0,      0);
        WINDOW* cmdsWin = newwin(10,     x, y - 9, 0);

        keypad(mainWin, TRUE);
        keypad(cmdsWin, TRUE);
        // keypad(mainWin, TRUE); // enables f1, f2, ... ; and also arrows keys
        // keypad(stdscr, TRUE); 
        // WINDOW* mainPad = newpad(y - 10, x);
        // WINDOW* commandsPad = newpad(10, x);


        NcursesColors::init();
        if (!NcursesColors::isColors())
        {
            waddwstr(mainWin, L"Colors are unsupported. Running without them!\n");
            wrefresh(mainWin);
        }
            
    #else
        std::wcout << L"Running without NCurses, colors are unsupported!\n";
    #endif
    

    Directory dir(".");

    if (!dir.exists())
    {
        #ifdef USE_N_CURSES
            NcursesColors::ERROR.on(mainWin);
                waddwstr(mainWin, L"Directory not found!\n");
            NcursesColors::ERROR.off(mainWin);
            wrefresh(mainWin);
        #else
            std::wcerr << L"Directory not found!\n";
        #endif
    }
    else
        dir.print(mainWin);
        

    mainLoop(dir, mainWin, cmdsWin);

    #ifdef USE_N_CURSES
        endwin();
    #endif

    return 0;
}
