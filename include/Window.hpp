#pragma once


#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
    #include <string>
#else
    #include <iostream>
#endif

#include <vector>
#include "Colors.hpp"

class Window
{
private:
    #ifdef USE_N_CURSES
        WINDOW* m_window;
    #endif

    int m_nlines, m_ncols;
    int m_virt_nlines, m_virt_ncols;

    int m_begin_y = 0, m_begin_x = 0;
    int m_y_offset = 0, m_x_offset = 0;
public:

    #ifdef USE_N_CURSES
        Window(
            int nlines, int ncols,
            int begin_y = 0, int begin_x = 0,
            int virt_nlines = 400, int virt_ncols = 200
        )
        : m_nlines(nlines), m_ncols(ncols), 
          m_begin_y(begin_y), m_begin_x(begin_x),
          m_virt_nlines(virt_nlines), m_virt_ncols(virt_ncols)
        {
            m_window = newpad(virt_nlines, virt_ncols);

            keypad(m_window, TRUE);

            clear();
        }

        WINDOW* get_ptr() const
        { 
            return m_window;
        }

    #else
        Window(
            int nlines, int ncols,
            int begin_y = 0, int begin_x = 0,
            int virt_nlines = 400, int virt_ncols = 200
        )
        : m_nlines(nlines), m_ncols(ncols), 
          m_begin_y(begin_y), m_begin_x(begin_x),
          m_virt_nlines(virt_nlines), m_virt_ncols(virt_ncols)
        {}
    #endif

    void scrollY(int dy = 1)
    {
        m_y_offset += dy;

        if (m_y_offset < 0)
            m_y_offset = 0;

        if (m_y_offset >= m_virt_nlines - m_nlines)
            m_y_offset = m_virt_nlines - m_nlines - 1;
    }

    void scrollX(int dx = 1)
    {
        m_x_offset += dx;

        
        if (m_x_offset < 0)
            m_x_offset = 0;

        
        if (m_x_offset >= m_virt_ncols - m_ncols)
            m_x_offset = m_virt_ncols - m_ncols - 1;
    }

    void clear() const
    {
        #ifdef USE_N_CURSES
            wclear(m_window);
        #endif
    }

    void print(
        std::wstring str, 
        const NcursesColors::COLOR_STRUCT& color = NcursesColors::FS_Regular
    ) const
    {
        #ifdef USE_N_CURSES
            color.on(m_window);
                waddwstr(m_window, str.c_str());
            color.off(m_window);
        #else
            std::wcout << str;
        #endif

    }

    void refresh() const
    {
        #ifdef USE_N_CURSES
            prefresh(
                m_window,
                m_y_offset, m_x_offset,
                m_begin_y, m_begin_x,
                m_begin_y + m_nlines - 1,
                m_begin_x + m_ncols - 1
            );
        #endif
    }

    void printr(
        std::wstring str, 
        const NcursesColors::COLOR_STRUCT& color = NcursesColors::FS_Regular
    ) const
    {
        print(str, color);
        refresh();
    }

    void printcr(
        std::wstring str, 
        const NcursesColors::COLOR_STRUCT& color = NcursesColors::FS_Regular
    ) const
    {
        clear();
        printr(str, color);
    }

};