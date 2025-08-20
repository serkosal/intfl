#pragma once

#ifndef INTFL_INIT_APP_HPP_
#define INTFL_INIT_APP_HPP_

#include <string>

#include <CLI/CLI.hpp>

#include "Window.hpp"
#include "Directory.hpp"
#include "Types.hpp"

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

        mutable std::wstring M_error_msg = L"";
        CLI::App M_cli_app = CLI::App{"INTeractive File Listing"};

        App() {};
        ~App();
        App(const App&) = delete;
        App& operator=(const App&) = delete;

    public:

        Window M_mainWin;
        Window M_cmdsWin;
        Flags M_flags;

        const Directory& getDir() const
        {   return M_dir; }

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
            M_mainWin.print(wstr + L"\n", true, true);
        }

        std::wstring getError() const
        {   return M_error_msg; }


        /**
         * @brief used for wait user's input before exit program.
         * 
         */
        int waitInput();


        /**
         * @brief init app's underline systems such as mouse input, colors, etc
         * 
         * @param argc arguments count, from main(int argc, char* argv[]) 
         * @param argv arguments string, array from main(int argc, char* argv[])
         * @return non-zero integer value if any error occured.
         */
        int init(int argc, char* argv[]);


        /**
         * @brief contains application main cycle
         * 
         * @return non-zero integer value if any error occured.
         */
        int mainLoop();
    };

} //

#endif