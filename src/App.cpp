#include "App.hpp"

#include <vector>
#include <string>

#include "Commands.hpp"
#include "FileReprPrinter.hpp"
#include "HandleInput.hpp"

namespace intfl {

int App::mainLoop()
{
    std::vector<FilePrintRepr> reprs;

    if (M_flags.help) 
    {   
        printHelp();
        waitInput();

        return 0;
    }

    if (!M_dir.exists())
    {   App::M_mainWin.printr(L"Directory not found!\n", NcursesColors::error); }
    else
    {
        reprs = M_dir.toRepr(App::M_flags);
        redraw(App::M_mainWin, reprs);
    }

    


    std::wstring cmd = L"";
    auto cmd_read_status = getCommand(
        App::app(), reprs, cmd
    );

    while (cmd != L"quit")
    {
        if (M_flags.help) 
        {   
            printHelp();
            M_flags.help = false;
        }

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

                reprs = M_dir.toRepr(App::M_flags);
                for (const auto& repr : reprs)
                {   printFileRepr(repr, App::M_mainWin); }

                App::M_mainWin.refresh();
            }
        }
        else if (cmd == L"help")
        {
            M_flags.help = true;
        }
        else
        {
            App::M_cmdsWin.printr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                NcursesColors::error
            );
        }

        cmd_read_status = getCommand(
            App::app(), reprs, cmd
        );
    }

    return 0;
}

} // end of the 'intfl' namespace