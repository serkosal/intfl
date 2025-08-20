#pragma once

#ifndef INTFL_WINDOW_HPP_
#define INTFL_WINDOW_HPP_

#include <string>
#include <vector>

#include "Colors.hpp"

namespace intfl {

/**
 * @brief class encapsulates behaviour related to specific area of the screen.
 * 
 */
class Window
{
private:

    /// @brief void ptr to Ncurses which static casted to WINDOW
    void* MP_window = nullptr;

    int M_nlines = 0, M_ncols = 0;
    int M_virt_nlines = 400, M_virt_ncols = 200;

    int M_begin_y = 0, M_begin_x = 0;
    int M_y_offset = 0, M_x_offset = 0;
public:

    void init(
        int nlines, int ncols,
        int begin_y = 0, int begin_x = 0,
        int virt_nlines = 400, int virt_ncols = 200
    );

    int getWch(wint_t* wch) const;

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
    void clear() const;

    /**
     * @brief display all data to the screen
     * 
     */
    void refresh() const;


    /**
     * @brief print str to the window using color
     * 
     * @param str   string to be printed to the screen
     * @param color color to be used to print, by default fs_regular, which is
     *              white
     */
    void print(
        const std::wstring& str,
        bool refresh = false,
        bool clear = false,
        const Colors::Color& color = Colors::fs_regular
    ) const;


    void printErr(
        const std::wstring& str,
        bool refresh = false,
        bool clear = false,
        const Colors::Color& color = Colors::error
    ) const
    {   print(str, refresh, clear, color); }


    void printNotice(
        const std::wstring& str,
        bool refresh = false,
        bool clear = false,
        const Colors::Color& color = Colors::notice
    ) const
    {   print(str, refresh, clear, color); }
};

} // end of the 'intfl' namespace

#endif