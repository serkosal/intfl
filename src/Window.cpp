#include "Window.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#else
    #include <iostream>
#endif

namespace intfl {

    void Window::init(
        int nlines, int ncols,
        int begin_y, int begin_x,
        int virt_nlines, int virt_ncols
    )
    {
        M_nlines = nlines; M_ncols = ncols; 
        M_begin_y = begin_y; M_begin_x = begin_x;
        M_virt_nlines = virt_nlines; M_virt_ncols = virt_ncols;

        #ifdef USE_N_CURSES
            MP_window = newpad(M_virt_nlines, M_virt_ncols);

            keypad(static_cast<WINDOW*>(MP_window), TRUE);

            clear();
        #endif
    }


    int Window::getWch(wint_t* wch) const
    {
        int res;

        #ifdef USE_N_CURSES
            res = wget_wch(static_cast<WINDOW*>(MP_window), wch);
        #else

        #endif

        return res;
    }


    void Window::clear() const
    {
        #ifdef USE_N_CURSES
            wclear(static_cast<WINDOW*>(MP_window));
        #endif
    }

    void Window::print(
        const std::wstring& str,
        bool refresh,
        bool clear,
        const Colors::Color& color
    ) const
    {
        #ifdef USE_N_CURSES

            auto win = static_cast<WINDOW*>(MP_window);

            if (clear)
            {   this->clear(); }

            const bool is_colors = Colors::isColors();

            if (is_colors) 
            {   wattron(win, COLOR_PAIR(color.getId())); }

            waddwstr(win, str.c_str());

            if (is_colors)
            {   wattroff(win, COLOR_PAIR(color.getId())); }

            if (refresh)
            {   this->refresh(); }
        #else
            std::wcout << str;
        #endif

    }

    void Window::refresh() const
    {
        #ifdef USE_N_CURSES
            prefresh(
                static_cast<WINDOW*>(MP_window),
                M_y_offset, M_x_offset,
                M_begin_y, M_begin_x,
                M_begin_y + M_nlines - 1,
                M_begin_x + M_ncols - 1
            );
        #endif
    }

} // end of the 'intfl' namespace