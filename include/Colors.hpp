#pragma once

#ifndef INTFL_COLORS_HPP_
#define INTFL_COLOR_HPP_

#include <array>

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
    #include <cstring>
#else
    #include <iostream>
    
    enum {
        COLOR_BLACK,
        COLOR_YELLOW,
        COLOR_RED,
        COLOR_WHITE,
        COLOR_BLUE,
        COLOR_GREEN
    };

#endif

namespace intfl 
{

/**
 * @brief class encapsulating ncurses colors specific methods & data 
 * 
 */
class NcursesColors {

public:

    // TYPES

    /**
     * @brief represents NcursesColor pair
     * 
     */
    class Color {
        friend class NcursesColors;

        inline static short MS_last_id {0};

        short M_id;
        short M_fg;
        short M_bg;

        Color(short fg, short bg)
        : M_fg{fg}, M_bg{bg}
        { 
            M_id = ++MS_last_id;
        }


        Color(short fg)
        : Color(fg, COLOR_BLACK) 
        {}

    public:

        #ifdef USE_N_CURSES
        void on(WINDOW* const P_win) const 
        {
            if (NcursesColors::isColors()) 
            {   wattron(P_win, COLOR_PAIR(M_id)); }
        }

        void off(WINDOW* const P_win) const 
        { 
            if (NcursesColors::isColors()) 
            {   wattroff(P_win, COLOR_PAIR(M_id)); }
        }
        #else
        void on() const {}
        void off() const {}
        #endif


    };

    // breaking style guide for using 'k', 's' identificators prefixes
    // in purpose of more convenient usage
    inline static const Color
        notice        = Color(COLOR_YELLOW),
        error         = Color(COLOR_RED),
        fs_regular    = Color(COLOR_WHITE),
        fs_directory  = Color{COLOR_BLUE},
        fs_executable = Color{COLOR_GREEN};
private:

    inline static bool MS_hasColors = false;

    // array to register colors
    inline static auto MS_colors = std::to_array<Color>({
        notice,
        error,
        fs_regular,
        fs_directory,
        fs_executable
    });

// METHODS
public:

    static bool isColors() { return MS_hasColors; }

    static void init()
    {
        #ifdef USE_N_CURSES
            MS_hasColors = has_colors();

            if(MS_hasColors)
            {	
                start_color();
                for (short i = 0; i < MS_colors.size(); ++i) 
                {
                    init_pair(
                        MS_colors[i].M_id, MS_colors[i].M_fg, MS_colors[i].M_bg
                    ); 
                }
            }
        #endif
    }
};

} // end of the 'intfl' namespace

#endif

