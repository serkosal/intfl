// intfl - interactive file listing program

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES

#include "App.hpp"
#include "Directory.hpp"


// #include "Colors.hpp"

// #include "MainLoop.hpp"
// #include "Window.hpp"
// #include "FileReprPrinter.hpp"
// #include "HandleInput.hpp"

using namespace intfl;

int main(int argc, char *argv[])
{
    auto res = App::app().init(argc, argv);
    if (res)
    {
        App::app().M_mainWin.printr(
            App::app().getError()
            + L"\nReturn code error is: " + std::to_wstring(res) + L"\n",
            NcursesColors::error
        );

        App::app().waitInput();

        return res;
    }

    res = App::app().mainLoop();
    if (res)
    {
        App::app().M_mainWin.printcr(
            L"\nProgram aborted! Error code is: " + std::to_wstring(res) + L"\n",
            NcursesColors::error
        );

        App::app().waitInput();
        return res;
    }
    

    return res;
}
