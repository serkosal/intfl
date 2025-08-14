// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#else
    #include <iostream>
#endif

#include <iostream>

#include "Colors.hpp"
#include "Directory.hpp"
#include "MainLoop.hpp"
#include "Window.hpp"
#include "FileReprPrinter.hpp"
#include "HandleInput.hpp"

int main(int argc, char *argv[])
{
    int y = 0, x = 0;

    auto path = std::filesystem::path(argv[0]).parent_path();

    // ncurses.h init
    #ifdef USE_N_CURSES
        setlocale(LC_ALL, "en_US.UTF-8");
        initscr();
        cbreak(); /* Line buffering disabled. pass on everything */
        noecho();

        mmask_t old_mmask;
        mousemask(BUTTON1_CLICKED | BUTTON_SHIFT | BUTTON_CTRL | BUTTON_ALT, &old_mmask);

        getmaxyx(stdscr, y, x);
    #else
        std::wcout << L"Running without NCurses, colors are unsupported!\n";
    #endif

    Window mainWin(y - 10, x, 0, 0);
    Window cmdsWin(10, x, y - 10, 0, 100, x);

    NcursesColors::init();
    if (!NcursesColors::isColors())
        mainWin.printr(L"Colors are unsupported. Running without them!\n", NcursesColors::ERROR);

    Directory dir(path);

    mainLoop(dir, mainWin, cmdsWin, argc, argv);

    #ifdef USE_N_CURSES
        endwin();
    #endif

    return 0;
}
