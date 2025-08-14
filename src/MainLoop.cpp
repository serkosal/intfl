#include "MainLoop.hpp"

#include <cstring>

#include "HandleInput.hpp"
#include "Commands.hpp"
#include "FileReprPrinter.hpp"

void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
)
{

    std::vector<FilePrintRepr> reprs;
    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        command_help(mainWin);
    else
    {
        if (!dir.exists())
            mainWin.printr(L"Directory not found!\n", NcursesColors::ERROR);
        else
        {
            reprs = dir.to_repr();
            mainWin.clear();
            for (const auto& repr : reprs)
                printFileRepr(repr, mainWin);
            mainWin.refresh();
        }
    }

    std::wstring cmd = L"";
    auto cmd_read_status = get_command(cmdsWin, mainWin, reprs, cmd);
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

            if (reprs.size())
            {
                mainWin.clear();
                for (const auto& repr : reprs)
                    printFileRepr(repr, mainWin);
                mainWin.refresh();
            }
        }
        else if (cmd == L"update")
        {
            if (!dir.exists())
                mainWin.printr(L"Directory not found!\n", NcursesColors::ERROR);
            else
            {
                reprs.clear();
                mainWin.clear();
                reprs = dir.to_repr();
                for (const auto& repr : reprs)
                    printFileRepr(repr, mainWin);
                mainWin.refresh();
            }
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

        cmd_read_status = get_command(cmdsWin, mainWin, reprs, cmd);
    }
}
