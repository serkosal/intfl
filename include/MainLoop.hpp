#pragma once

#include <string>

#include "Directory.hpp"
#include "HandleInput.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include <cstring>
#else
    #include <iostream>
#endif

#include "Colors.hpp"
#include "Window.hpp"


void mainLoop(
    const Directory &dir,
    const Window& mainWin,
    const Window& cmdsWin
)
{
    InputHandler mainInputHandler;

    std::wstring cmd = L"";
    auto cmd_read_status = mainInputHandler.get_command(cmdsWin, cmd);
    while (cmd != L"quit")
    {
        if (cmd_read_status)
        {
            cmdsWin.printcr(L"\nAn error occured while handling command input!\n", NcursesColors::ERROR);
            
            continue;
        }

        if (cmd == L"redraw")
        {
            mainWin.clear();
            dir.print(mainWin);
        }
        else if (cmd == L"help")
        {
            cmdsWin.printr(
                L"\nUse commands:\n\nquit\nredraw\n",
                NcursesColors::NOTICE
            );
        }
        else
        {
            cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::ERROR
            );
        }

        cmd_read_status = mainInputHandler.get_command(cmdsWin, cmd);
    }
}
