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

    std::wstring cmd = L"";
    auto cmd_read_status = mainInputHandler.get_command(cmd);
    while (cmd != L"quit")
    {
        if (cmd_read_status)
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

        if (cmd == L"redraw")
        {
            #ifdef USE_N_CURSES
                clear();
                dir.print();
                refresh();
            #else
                dir.print();
            #endif
        }
        else if (cmd == L"help")
        {
            #ifdef USE_N_CURSES
                NcursesColors::NOTICE.on();
                    addwstr(L"\nUse commands:\n\nquit\nredraw\n");
                NcursesColors::NOTICE.off();
                refresh();
            #else
                std::wcout << "Use commands:\nquit\nredraw\n";
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

        cmd_read_status = mainInputHandler.get_command(cmd);
    }
}
