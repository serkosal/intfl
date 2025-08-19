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
#else
    #include <iostream>
#endif

namespace intfl {

/**
 * @brief class encapsulates behaviour related to specific area of the screen.
 * 
 */
class Window
{
private:
    #ifdef USE_N_CURSES
        WINDOW* MP_window = nullptr;
    #endif

    int M_nlines = 0, M_ncols = 0;
    int M_virt_nlines = 400, M_virt_ncols = 200;

    int M_begin_y = 0, M_begin_x = 0;
    int M_y_offset = 0, M_x_offset = 0;
public:

    void init(
        int nlines, int ncols,
        int begin_y = 0, int begin_x = 0,
        int virt_nlines = 400, int virt_ncols = 200
    )
    {
        M_nlines = nlines; M_ncols = ncols; 
        M_begin_y = begin_y; M_begin_x = begin_x;
        M_virt_nlines = virt_nlines; M_virt_ncols = virt_ncols;

        #ifdef USE_N_CURSES
            MP_window = newpad(M_virt_nlines, M_virt_ncols);

            keypad(MP_window, TRUE);

            clear();
        #endif
    }

    Window() {}

    /**
     * @brief Construct a new Window object
     * 
     * @param nlines        number of lines
     * @param ncols         number of columns
     * @param begin_y       y position to start draw the window
     * @param begin_x       x position to start draw the window
     * @param virt_nlines   how many lines alocated in memory for data
     * @param virt_ncols    how many columns alocated in memory for data
     */
    Window(
        int nlines, int ncols,
        int begin_y = 0, int begin_x = 0,
        int virt_nlines = 400, int virt_ncols = 200
    )
    : M_nlines(nlines), M_ncols(ncols), 
      M_begin_y(begin_y), M_begin_x(begin_x),
      M_virt_nlines(virt_nlines), M_virt_ncols(virt_ncols)
    {
        init(nlines, ncols, begin_y, begin_x, virt_nlines, virt_ncols);
    }

    #ifdef USE_N_CURSES
        WINDOW* getPtr() const
        { 
            return MP_window;
        }
    #endif

    
    int getYOffset() const noexcept { return M_y_offset; }
    int getXOffset() const noexcept { return M_y_offset; }

    /**
     * @brief adds dy to the y_offset
     * 
     * @param dy 
     */
    void scrollY(int dy = 1)
    {
        M_y_offset += dy;

        if (M_y_offset < 0)
        {   M_y_offset = 0; }

        if (M_y_offset >= M_virt_nlines - M_nlines)
        {   M_y_offset = M_virt_nlines - M_nlines - 1; }
    }

    /**
     * @brief adds dx to the x_offset
     * 
     * @param dx 
     */
    void scrollX(int dx = 1)
    {
        M_x_offset += dx;

        
        if (M_x_offset < 0)
        {   M_x_offset = 0; }

        
        if (M_x_offset >= M_virt_ncols - M_ncols)
        {   M_x_offset = M_virt_ncols - M_ncols - 1; }
    }

    /**
     * @brief clears screen, does nothing without ncurses library
     * 
     */
    void clear() const
    {
        #ifdef USE_N_CURSES
            wclear(MP_window);
        #endif
    }

    /**
     * @brief print str to the window using color
     * 
     * @param str   string to be printed to the screen
     * @param color color to be used to print, by default fs_regular, which is
     *              white
     */
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

    /**
     * @brief display all data to the screen
     * 
     */
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

    /**
     * @brief same as print and then refresh
     * 
     * @param str 
     * @param color 
     */
    void printr(
        std::wstring str, 
        const NcursesColors::Color& color = NcursesColors::fs_regular
    ) const
    {
        print(str, color);
        refresh();
    }

    /**
     * @brief same as clear and then printr
     * 
     * @param str 
     * @param color 
     */
    void printcr(
        std::wstring str, 
        const NcursesColors::Color& color = NcursesColors::fs_regular
    ) const
    {
        clear();
        printr(str, color);
    }

};

} // end of the 'intfl' namespace

#endif