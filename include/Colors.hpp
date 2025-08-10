#pragma once

#include <array>

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

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


class NcursesColors {
// STATIC-FIELDS
public:
    // TYPES
    class COLOR_STRUCT {
        friend class NcursesColors;

        inline static short last_id = 0;

        short id;
        short fg;
        short bg;

        COLOR_STRUCT(short fg, short bg)
        : fg{fg}, bg{bg}
        { 
            id = ++last_id;
        }


        COLOR_STRUCT(short fg)
        : COLOR_STRUCT(fg, COLOR_BLACK) 
        {}

    public:

        #ifdef USE_N_CURSES
        void on(WINDOW* win) const
        { 
           
            if (NcursesColors::isColors())
                wattron(win, COLOR_PAIR(id));
            
        }

        void off(WINDOW* win) const
        { 
            if (NcursesColors::isColors())
                wattroff(win, COLOR_PAIR(id)); 
        }
        #else
        void on() const {}
        void off() const {}
        #endif


    };

    inline static const COLOR_STRUCT
        NOTICE        = COLOR_STRUCT(COLOR_YELLOW),
        ERROR         = COLOR_STRUCT(COLOR_RED),
        FS_Regular    = COLOR_STRUCT(COLOR_WHITE),
        FS_Directory  = COLOR_STRUCT{COLOR_BLUE},
        FS_Executable = COLOR_STRUCT{COLOR_GREEN};
private:

    inline static bool hasColors = false;

    // array to register colors
    inline static auto colors = std::to_array<COLOR_STRUCT>({
        NOTICE,
        ERROR,
        FS_Regular,
        FS_Directory,
        FS_Executable
    });

// METHODS
public:

    static bool isColors()
    { return hasColors; }

    static void init()
    {
        #ifdef USE_N_CURSES
            hasColors = has_colors();

            if(hasColors)
            {	
                start_color();
                for (short i = 0; i < colors.size(); ++i)
                    init_pair(colors[i].id, colors[i].fg, colors[i].bg);
            }
        #endif
    }
};