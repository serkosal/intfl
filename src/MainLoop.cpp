#include "MainLoop.hpp"

#include <cstring>

#include "HandleInput.hpp"
#include "Commands.hpp"
#include "FileReprPrinter.hpp"

namespace intfl {

void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
)
{
    std::vector<FilePrintRepr> reprs;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        commandHelp(mainWin);
    else
    {
        if (!dir.exists())
            mainWin.printr(L"Directory not found!\n", NcursesColors::error);
        else
        {
            reprs = dir.toRepr();
            redraw(mainWin, reprs);
        }
    }

    std::wstring cmd = L"";
    auto cmd_read_status = getCommand(cmdsWin, mainWin, dir, reprs, cmd);
    while (cmd != L"quit")
    {
        if (cmd_read_status)
        {
            cmdsWin.printcr(L"\nAn error occured while handling command input!\n", NcursesColors::error);
            
            continue;
        }

        if (cmd == L"redraw")
        {
            mainWin.clear();
            redraw(mainWin, reprs);
        }
        else if (cmd == L"update")
        {
            if (!dir.exists())
                mainWin.printr(L"Directory not found!\n", NcursesColors::error);
            else
            {
                reprs.clear();
                mainWin.clear();
                reprs = dir.toRepr();
                for (const auto& repr : reprs)
                    printFileRepr(repr, mainWin);
                mainWin.refresh();
            }
        }
        else if (cmd == L"help")
        {
            commandHelp(mainWin);
        }
        else
        {
            cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::error
            );
        }

        cmd_read_status = getCommand(cmdsWin, mainWin, dir, reprs, cmd);
    }
}

}