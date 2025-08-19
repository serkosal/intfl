#pragma once

#ifndef INTFL_INIT_APP_HPP_
#define INTFL_INIT_APP_HPP_

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#else
    #include <iostream>
#endif

#include <filesystem>
#include <locale>
#include <map>
#include <string>

#include <CLI/CLI.hpp>

#include "Colors.hpp"
#include "Window.hpp"
#include "Directory.hpp"

namespace intfl {

    struct Flags
    {
        bool all{false},
             dirs_only{false},
             prune{false},
             full_filenames{false},
             user{false},
             group{false},
             size{false},
             disk_usage{false},
             no_colors{false},
             ascii{false},
             help{false};
        
        size_t print_max_depth = 5;
        size_t files_limit = 15;
    };


    /**
     * @brief Singleton class represents console Application
     * 
     */
    class App
    {
    private:
        int M_width, M_height;   // represents terminal size 

        bool M_supportsNcurses;
        bool M_hasColors;
        bool M_hasWchar;
        bool M_supportMouseInput;

        Directory M_dir;

        mutable std::wstring M_error_msg = L"";
        CLI::App M_cli_app = CLI::App{"INTeractive File Listing"};

        App() {};
        ~App() 
        {
            #ifdef USE_N_CURSES 
                endwin();
            #endif
        }
        App(const App&) = delete;
        App& operator=(const App&) = delete;

    public:

        Window M_mainWin;
        Window M_cmdsWin;
        Flags M_flags;

        /**
         * @brief get an app singleton instance
         * 
         */
        static App& app() 
        {
            static App instance;

            return instance;
        }

        void printHelp() const
        {
            auto help_str = M_cli_app.help("", CLI::AppFormatMode::All);
            std::wstring wstr(help_str.begin(), help_str.end());
            M_mainWin.printcr(wstr + L"\n"); 
        }

        std::wstring getError() const
        {   return M_error_msg; }


        /**
         * @brief used for wait user's input before exit program.
         * 
         */
        int waitInput()
        {
            std::wstring cmd = L"";
            #ifdef USE_N_CURSES
                wint_t wch;
                auto res = wget_wch(M_cmdsWin.getPtr(), &wch);

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
                            M_cmdsWin.printcr(cmd);
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
                        M_cmdsWin.printr(std::wstring(buf));
                    }

                    res = wget_wch(M_cmdsWin.getPtr(), &wch);
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


        /**
         * @brief init app's underline systems such as mouse input, colors, etc
         * 
         * @param argc arguments count, from main(int argc, char* argv[]) 
         * @param argv arguments string, array from main(int argc, char* argv[])
         * @return non-zero integer value if any error occured.
         */
        int init(int argc, char* argv[]) 
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

                NcursesColors::init();
                if (!NcursesColors::isColors())
                {   M_mainWin.printr(
                        L"Colors are unsupported. Running without them!\n", 
                        NcursesColors::error
                    );
                }
            #else
                std::wcout << L"Running without NCurses, colors are unsupported!\n";
            #endif

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
                    M_cmdsWin.printr(
                        L"intfl v0.1.1-alpha\n"
                    );
                },
                "shows intfl's version"
            );

            auto path = std::filesystem::path(argv[0]).parent_path();

            M_dir.init(path);

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

            return 0;
        }

        /**
         * @brief contains application main cycle
         * 
         * @return non-zero integer value if any error occured.
         */
        int mainLoop();
    };

} //

#endif