#pragma once

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include <string>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

class Window
{
private:
    #ifdef USE_N_CURSES
        WINDOW* m_window;
    #endif

    int m_lines, m_columns, m_height, m_width;
public:

    #ifdef USE_N_CURSES
        Window(int lines, int columns, int height, int width)
        : m_lines(lines), m_columns(columns), m_height(height), m_width(width)
        {
            m_window = newwin(lines, columns, height, width);

            keypad(m_window, TRUE);
        }

        WINDOW* get_ptr() const
        { return m_window; }
    #else
        Window(int lines, int columns, int height, int width)
        : m_lines(lines), m_columns(columns), m_height(height), m_width(width)
        {}
    #endif

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
            wrefresh(m_window);
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