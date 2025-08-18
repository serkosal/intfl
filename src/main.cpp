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
            L"Couldn't initialize intfl error code is: "
            + std::to_wstring(res)
            + L"\n"
        );
    }

    res = App::app().mainLoop();
    if (res)
    {
        App::app().M_mainWin.printr(
            L"Program aborted! Error code is: " + std::to_wstring(res) + L"\n"
        );
    }
    

    return res;
}
