#include "MainLoop.hpp"

#include <cstring>

#include "HandleInput.hpp"
#include "Commands.hpp"

void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
)
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        command_help(mainWin);
    else
    {
        if (!dir.exists())
            mainWin.printr(L"Directory not found!\n", NcursesColors::ERROR);
        else
            dir.print(mainWin);
    }

    std::wstring cmd = L"";
    auto cmd_read_status = get_command(cmdsWin, mainWin, cmd);
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

            if (!dir.exists())
                mainWin.printr(L"Directory not found!\n", NcursesColors::ERROR);
            else
                dir.print(mainWin);
        }
        else if (cmd == L"help")
        {
            command_help(mainWin);
        }
        else
        {
            cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::ERROR
            );
        }

        cmd_read_status = get_command(cmdsWin, mainWin, cmd);
    }
}
