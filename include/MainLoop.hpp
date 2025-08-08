#pragma once

#include <string>

#include "Directory.hpp"
#include "HandleInput.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include <cstring>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

void mainLoop(const Directory &dir)
{
    InputHandler mainInputHandler;

    auto res = mainInputHandler.get_command();
    while (mainInputHandler.command != L"quit")
    {
        if (res)
        {
            #ifdef USE_N_CURSES
                NcursesColors::ERROR.on();
                    addwstr(L"\nAn error occured while handling command input!\n");
                NcursesColors::ERROR.off();
            #else
                std::wcerr << L"\nAn error occured while handling command input!\n";
            #endif
            
            continue;
        }

        if (mainInputHandler.command == L"redraw")
        {
            #ifdef USE_N_CURSES
                clear();
                dir.print();
                refresh();
            #else
                dir.print();
            #endif
        }
        else if (mainInputHandler.command == L"help")
        {
            #ifdef USE_N_CURSES
                NcursesColors::NOTICE.on();
                    addwstr(L"\nquit\nredraw\n");
                NcursesColors::NOTICE.off();
                refresh();
            #else
                dir.print();
            #endif
        }
        else
        {
            #ifdef USE_N_CURSES
                NcursesColors::ERROR.on();
                    addwstr(L"\nUnrecognized command!\nType help to see commands list\n");
                NcursesColors::ERROR.off();
                refresh();
            #else
                std::wcout << "Unrecognized command!\nType help to see commands list\n";
            #endif
        }

        res = mainInputHandler.get_command();
    }
}
