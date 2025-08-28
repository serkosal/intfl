#include "App.hpp"

#include <vector>
#include <string>

#include "FileReprPrinter.hpp"
#include "HandleInput.hpp"

#include <CLI/CLI.hpp>

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#else
    #include <iostream>
#endif

namespace intfl {

int App::init(int argc, char* argv[]) 
{
    std::locale::global(std::locale("en_US.UTF-8"));
    // ncurses.h init
    #ifdef USE_N_CURSES
        
        initscr();
        cbreak(); /* Line buffering disabled. pass on everything */
        noecho();

        mmask_t old_mmask;
        mousemask(
            BUTTON1_CLICKED | BUTTON_SHIFT | BUTTON_CTRL | BUTTON_ALT, 
            &old_mmask
        );

        getmaxyx(stdscr, M_height, M_width);

        M_mainWin.init(M_height - 10, M_width, 0, 0);
        M_cmdsWin.init(10, M_width, M_height - 10, 0, 100, M_width);

        M_mainWin.clear();
        M_cmdsWin.clear();

        Colors::init();
    #endif

    if (!Colors::isColors())
    {   M_mainWin.printErr(
            L"Colors are unsupported. Running without them!\n", 
            true
        );
    }

    M_cli_app.add_flag("-a, --all", M_flags.all, 
        "prints files which filenames started from '.', "
        "with exception for `.` and `..`."
    );

    M_cli_app.add_flag("-d, --dirs-only", M_flags.dirs_only, 
        "prints directories only."
    );

    M_cli_app.add_flag("--ascii", M_flags.ascii, 
        "prints ascii-only graphics."
    );

    M_cli_app.add_flag("--no-colors", M_flags.no_colors, 
        "print without usage of colors."
    );

    M_cli_app.add_flag("--du, --disk-usage", M_flags.disk_usage, 
        "calculate dir sizes using their content."
    );

    M_cli_app.add_flag("-f, --print-filepathes", M_flags.full_filenames, 
        "prints pathes to files instead just theirs filenames."
    );

    M_cli_app.add_flag("-g, --group", M_flags.group, 
        "prints the group that owning file."
    );

    M_cli_app.add_flag("-u, --user", M_flags.user, 
        "prints the user that owning file."
    );


    M_cli_app.add_flag("-s, --size", M_flags.size, 
        "prints size of files."
    );

    M_cli_app.add_flag("--prune", M_flags.prune, 
        "do not print empty directories."
    );

    M_cli_app.add_flag(
        "-v,--version",

        [this](size_t n)
        {
            M_cmdsWin.print(
                L"intfl v0.3.1-alpha\n",
                true
            );
        },
        "shows intfl's version"
    );

    auto path = std::filesystem::path(argv[0]).parent_path();

    // CLI11_PARSE
    try 
    {   M_cli_app.parse(argc, argv); }
    catch (const CLI::ParseError &e)
    {
        if(e.get_name() == "RuntimeError")
        {   return e.get_exit_code(); }

        else if(e.get_name() == "CallForHelp") 
        {
            M_flags.help = true;
        }
        else if(e.get_name() == "CallForAllHelp") 
        {
            M_flags.help = true;
        }

        auto err_str = CLI::FailureMessage::simple(&M_cli_app, e);
        M_error_msg = std::wstring(err_str.begin(), err_str.end());

        return e.get_exit_code();
    }

    M_dir.init(path);

    return 0;
}

// void App::redraw(const std::vector<FilePrintRepr>& reprs) const
// {
//     win.clear();
//     for (const auto& repr : reprs)
//     {   printFileRepr(repr, win); }
//     win.refresh();
// }

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
    {   App::M_mainWin.printErr(L"Directory not found!\n", true); }
    else
    {
        reprs = M_dir.toRepr(App::M_flags);
        M_mainWin.clear();
        for (const auto& repr : reprs)
        {   printFileRepr(repr, M_mainWin); }
        M_mainWin.refresh();
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
            App::M_cmdsWin.printErr(
                L"\nAn error occured while handling command input!\n", 
                true, true
            );
            
            continue;
        }

        if (cmd == L"redraw")
        {
            App::M_mainWin.clear(); 
            for (const auto& repr : reprs)
            {   printFileRepr(repr, M_mainWin); }
            M_mainWin.refresh();
        }
        else if (cmd == L"update")
        {
            if (!M_dir.exists())
            { 
                App::M_mainWin.printErr(
                    L"Directory not found!\n", true
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
            App::M_cmdsWin.printErr(
                L"\nUnrecognized command!\nType help to see commands list\n",
                true
            );
        }

        cmd_read_status = getCommand(
            App::app(), reprs, cmd
        );
    }

    return 0;
}

int App::waitInput()
{
    std::wstring cmd = L"";
    #ifdef USE_N_CURSES
        wint_t wch;
        
        auto res = M_cmdsWin.getWch(&wch);

        while (wch != WEOF && wch != L'\n' && wch != L'\r')
        {
            if (res == KEY_CODE_YES)
            {
                if (wch == KEY_ENTER || wch == KEY_END)
                {
                    cmd = L"";
                    break;
                }
                else if (wch == KEY_BACKSPACE && cmd.size())
                {
                    cmd.resize(cmd.size() - 1);
                    M_cmdsWin.print(cmd, true, true);
                }
            }
            else if (res == ERR)
            {
                cmd = L"";
                return 1;
            }
            else if (res == OK && !std::iswcntrl(wch))
            {
                cmd += static_cast<wchar_t>(wch);
                wchar_t buf[2] = {static_cast<wchar_t>(wch), L'\0'};
                M_cmdsWin.print(std::wstring(buf), true);
            }

            res = M_cmdsWin.getWch(&wch);
        }
        M_cmdsWin.clear();
        M_cmdsWin.refresh();
    #else
        auto &res = std::getline(std::wcin, cmd);
        if (res.fail())
        {   return 1; }
    #endif

    return 0;
}

App::~App()
{
    #ifdef USE_N_CURSES 
        endwin();
    #endif
}

} // end of the 'intfl' namespace