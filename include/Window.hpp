#pragma once

#ifndef INTFL_WINDOW_HPP_
#define INTFL_WINDOW_HPP_

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES

#include <string>
#include <vector>

#include "Colors.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
    #include <string>
#else
    #include <iostream>
#endif

namespace intfl {

class Window
{
private:
    #ifdef USE_N_CURSES
        WINDOW* MP_window;
    #endif

    int M_nlines, M_ncols;
    int M_virt_nlines, M_virt_ncols;

    int M_begin_y = 0, M_begin_x = 0;
    int M_y_offset = 0, M_x_offset = 0;
public:

    #ifdef USE_N_CURSES
        Window(
            int nlines, int ncols,
            int begin_y = 0, int begin_x = 0,
            int virt_nlines = 400, int virt_ncols = 200
        )
        : M_nlines(nlines), M_ncols(ncols), 
          M_begin_y(begin_y), M_begin_x(begin_x),
          M_virt_nlines(virt_nlines), M_virt_ncols(virt_ncols)
        {
            MP_window = newpad(virt_nlines, virt_ncols);

            keypad(MP_window, TRUE);

            clear();
        }

        WINDOW* getPtr() const
        { 
            return MP_window;
        }

    #else
        Window(
            int nlines, int ncols,
            int begin_y = 0, int begin_x = 0,
            int virt_nlines = 400, int virt_ncols = 200
        )
        : M_nlines(nlines), M_ncols(ncols), 
          M_begin_y(begin_y), M_begin_x(begin_x),
          M_virt_nlines(virt_nlines), M_virt_ncols(virt_ncols)
        {}
    #endif

    void scrollY(int dy = 1)
    {
        M_y_offset += dy;

        if (M_y_offset < 0)
            M_y_offset = 0;

        if (M_y_offset >= M_virt_nlines - M_nlines)
            M_y_offset = M_virt_nlines - M_nlines - 1;
    }

    void scrollX(int dx = 1)
    {
        M_x_offset += dx;

        
        if (M_x_offset < 0)
            M_x_offset = 0;

        
        if (M_x_offset >= M_virt_ncols - M_ncols)
            M_x_offset = M_virt_ncols - M_ncols - 1;
    }

    void clear() const
    {
        #ifdef USE_N_CURSES
            wclear(MP_window);
        #endif
    }

    void print(
        std::wstring str, 
        const NcursesColors::Color& color = NcursesColors::fs_regular
    ) const
    {
        #ifdef USE_N_CURSES
            color.on(MP_window);
                waddwstr(MP_window, str.c_str());
            color.off(MP_window);
        #else
            std::wcout << str;
        #endif

    }

    void refresh() const
    {
        #ifdef USE_N_CURSES
            prefresh(
                MP_window,
                M_y_offset, M_x_offset,
                M_begin_y, M_begin_x,
                M_begin_y + M_nlines - 1,
                M_begin_x + M_ncols - 1
            );
        #endif
    }

    void printr(
        std::wstring str, 
        const NcursesColors::Color& color = NcursesColors::fs_regular
    ) const
    {
        print(str, color);
        refresh();
    }

    void printcr(
        std::wstring str, 
        const NcursesColors::Color& color = NcursesColors::fs_regular
    ) const
    {
        clear();
        printr(str, color);
    }

};

}

#endif