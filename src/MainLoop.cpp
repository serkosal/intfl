#include "MainLoop.hpp"

#include <cstring>

#include "HandleInput.hpp"
#include "Commands.hpp"
#include "FileReprPrinter.hpp"

namespace intfl {

void mainLoop(
    const Directory& A_dir,
    Window& A_mainWin,
    Window& A_cmdsWin,
    int A_argc, char* A_argv[]
)
{
    std::vector<FilePrintRepr> reprs;

    if (A_argc > 1 && strcmp(A_argv[1], "--help") == 0)
    {   commandHelp(A_mainWin); }
    else
    {
        if (!A_dir.exists())
        {   A_mainWin.printr(L"Directory not found!\n", NcursesColors::error); }
        else
        {
            reprs = A_dir.toRepr();
            redraw(A_mainWin, reprs);
        }
    }

    std::wstring cmd = L"";
    auto cmd_read_status = getCommand(A_cmdsWin, A_mainWin, A_dir, reprs, cmd);
    while (cmd != L"quit")
    {
        if (cmd_read_status)
        {
            A_cmdsWin.printcr(
                L"\nAn error occured while handling command input!\n", 
                NcursesColors::error
            );
            
            continue;
        }

        if (cmd == L"redraw")
        {
            A_mainWin.clear();
            redraw(A_mainWin, reprs);
        }
        else if (cmd == L"update")
        {
            if (!A_dir.exists())
            { 
                A_mainWin.printr(
                    L"Directory not found!\n", NcursesColors::error
                );
            } 
            else
            {
                reprs.clear();
                A_mainWin.clear();

                reprs = A_dir.toRepr();
                for (const auto& repr : reprs)
                {   printFileRepr(repr, A_mainWin); }

                A_mainWin.refresh();
            }
        }
        else if (cmd == L"help")
        {
            commandHelp(A_mainWin);
        }
        else
        {
            A_cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::error
            );
        }

        cmd_read_status = getCommand(A_cmdsWin, A_mainWin, A_dir, reprs, cmd);
    }
}

} // end of the 'intfl' namespace