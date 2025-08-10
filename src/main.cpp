// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
    #include <cstring>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

#include "Directory.hpp"
#include "MainLoop.hpp"
#include "Window.hpp"

int main()
{
    int y = 0 , x = 0;

    // ncurses.h init
    #ifdef USE_N_CURSES

        setlocale(LC_ALL, "en_US.UTF-8");
        initscr();
        // cbreak(); /* Line buffering disabled. pass on everything */
        noecho();

        getmaxyx(stdscr, y, x);
    #else
        std::wcout << L"Running without NCurses, colors are unsupported!\n";
    #endif

    Window mainWin(y - 10, x, 0, 0);
    Window cmdsWin(10, x, y - 10, 0, 100, x);

    NcursesColors::init();
    if (!NcursesColors::isColors())
        mainWin.printr(L"Colors are unsupported. Running without them!\n", NcursesColors::ERROR);
    

    Directory dir(".");

    if (!dir.exists())
        mainWin.printr(L"Directory not found!\n", NcursesColors::ERROR);
    else
        dir.print(mainWin);
        
        
    #ifdef USE_N_CURSES
        mainLoop(dir, mainWin, cmdsWin);

        endwin();
    #else
        mainLoop(dir, mainWin, cmdsWin);
    #endif
    
    return 0;
}
