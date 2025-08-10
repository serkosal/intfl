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

#ifdef USE_N_CURSES
    void mainLoop(const Directory &dir, WINDOW* mainwin, WINDOW* cmdswin)
#else
    void mainLoop(const Directory &dir)
#endif
{
    InputHandler mainInputHandler;

    std::wstring cmd = L"";
    #ifdef USE_N_CURSES
        auto cmd_read_status = mainInputHandler.get_command(cmdswin, cmd);
    #else
        auto cmd_read_status = mainInputHandler.get_command(cmd);
    #endif
    while (cmd != L"quit")
    {
        if (cmd_read_status)
        {
            #ifdef USE_N_CURSES
                wclear(cmdswin);
                NcursesColors::ERROR.on(cmdswin);
                    waddwstr(cmdswin, L"\nAn error occured while handling command input!\n");
                NcursesColors::ERROR.off(cmdswin);
                wrefresh(cmdswin);
            #else
                std::wcerr << L"\nAn error occured while handling command input!\n";
            #endif
            
            continue;
        }

        if (cmd == L"redraw")
        {
            #ifdef USE_N_CURSES
                wclear(mainwin);
                dir.print(mainwin);
                wrefresh(mainwin);
            #else
                dir.print();
            #endif
        }
        else if (cmd == L"help")
        {
            #ifdef USE_N_CURSES
                NcursesColors::NOTICE.on(cmdswin);
                    waddwstr(cmdswin, L"\nUse commands:\n\nquit\nredraw\n");
                NcursesColors::NOTICE.off(cmdswin);
                wrefresh(cmdswin);
            #else
                std::wcout << "Use commands:\nquit\nredraw\n";
            #endif
        }
        else
        {
            #ifdef USE_N_CURSES
                NcursesColors::ERROR.on(cmdswin);
                    waddwstr(cmdswin, L"\nUnrecognized command!\nType help to see commands list\n");
                NcursesColors::ERROR.off(cmdswin);
                wrefresh(cmdswin);
            #else
                std::wcout << "Unrecognized command!\nType help to see commands list\n";
            #endif
        }

        #ifdef USE_N_CURSES
            auto cmd_read_status = mainInputHandler.get_command(cmdswin, cmd);
        #else
            auto cmd_read_status = mainInputHandler.get_command(cmd);
        #endif
    }
}
