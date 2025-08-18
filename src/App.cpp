#include <cstring>
#include <memory>
#include <forward_list>

#include "HandleInput.hpp"
#include "Commands.hpp"
#include "FileReprPrinter.hpp"

#include "App.hpp"


namespace intfl {

int App::mainLoop()
{
    std::vector<FilePrintRepr> reprs;

    if (M_argc > 1 && strcmp(M_argv[1], "--help") == 0)
    {   commandHelp(App::M_mainWin); }
    else
    {
        if (!M_dir.exists())
        {   App::M_mainWin.printr(L"Directory not found!\n", NcursesColors::error); }
        else
        {
            reprs = M_dir.toRepr();
            redraw(App::M_mainWin, reprs);
        }
    }

    std::wstring cmd = L"";
    auto cmd_read_status = getCommand(
        App::M_cmdsWin, App::M_mainWin, M_dir, reprs, cmd
    );
    while (cmd != L"quit")
    {
        if (cmd_read_status)
        {
            App::M_cmdsWin.printcr(
                L"\nAn error occured while handling command input!\n", 
                NcursesColors::error
            );
            
            continue;
        }

        if (cmd == L"redraw")
        {
            App::M_mainWin.clear();
            redraw(App::M_mainWin, reprs);
        }
        else if (cmd == L"update")
        {
            if (!M_dir.exists())
            { 
                App::M_mainWin.printr(
                    L"Directory not found!\n", NcursesColors::error
                );
            } 
            else
            {
                reprs.clear();
                App::M_mainWin.clear();

                reprs = M_dir.toRepr();
                for (const auto& repr : reprs)
                {   printFileRepr(repr, App::M_mainWin); }

                App::M_mainWin.refresh();
            }
        }
        else if (cmd == L"help")
        {
            commandHelp(App::M_mainWin);
        }
        else
        {
            App::M_cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::error
            );
        }

        cmd_read_status = getCommand(
            App::M_cmdsWin, App::M_mainWin, M_dir, reprs, cmd
        );
    }

    return 0;
}

} // end of the 'intfl' namespace