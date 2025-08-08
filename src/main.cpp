// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

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
        cbreak(); /* Line buffering disabled. pass on everything */
        noecho();
        keypad(stdscr, TRUE); // enables f1, f2, ... ; and also arrows keys

        NcursesColors::init();
        if (!NcursesColors::isColors())
            addwstr(L"Colors are unsupported. Running without them!\n");
    #else
        std::wcout << L"Running without NCurses, colors are unsupported!\n";
    #endif
    

    Directory dir(".");

    if (!dir.exists())
    {
        #ifdef USE_N_CURSES
            NcursesColors::ERROR.on();
                addwstr(L"Directory not found!\n");
            NcursesColors::ERROR.off();
            refresh();
        #else
            std::wcerr << L"Directory not found!\n";
        #endif
    }
    else 
        dir.print();

    mainLoop(dir);

    #ifdef USE_N_CURSES
        endwin();
    #endif

    return 0;
}
