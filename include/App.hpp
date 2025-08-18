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

#include "Colors.hpp"
#include "Window.hpp"
#include "Directory.hpp"

namespace intfl {

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

        int   M_argc;
        char** M_argv;

        // static std::map<std::string, std::wstring> flags; 

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

        /**
         * @brief get an app singleton instance
         * 
         * @param argc 
         * @param argv 
         */
        static App& app() 
        {
            static App instance;

            return instance;
        }

        // std::map<std::string, std::wstring> parse_flags();

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

            auto path = std::filesystem::path(argv[0]).parent_path();

            M_dir.init(path);

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