// intfl - interactive file listing program

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES

#include "App.hpp"

using namespace intfl;

int main(int argc, char *argv[])
{
    auto res = App::app().init(argc, argv);
    if (res)
    {
        App::app().M_mainWin.printErr(
            App::app().getError()
            + L"\nReturn code error is: " + std::to_wstring(res) + L"\n",
            true
        );

        App::app().waitInput();

        return res;
    }

    res = App::app().mainLoop();
    if (res)
    {
        App::app().M_mainWin.printErr(
            L"\nProgram aborted! Error code is: " + std::to_wstring(res) + L"\n",
            true, true
        );

        App::app().waitInput();
        return res;
    }
    

    return res;
}
