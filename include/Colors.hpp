#pragma once

#include <array>

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 

#ifdef USE_N_CURSES
    #include <ncurses.h>
    #include <cstring>
#else
    #include <iostream>
#endif


class NcursesColors {
// TYPES
    struct COLOR_STRUCT {

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

        void on() const
        { 
            if (NcursesColors::isColors())
                attron(COLOR_PAIR(id)); 
        }

        void off() const
        { 
            if (NcursesColors::isColors())
                attroff(COLOR_PAIR(id)); 
        }
    };

// STATIC-FIELDS
public:
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
        hasColors = has_colors();
        if(hasColors)
        {	start_color();
            for (short i = 0; i < colors.size(); ++i)
                init_pair(colors[i].id, colors[i].fg, colors[i].bg);
        }
    }
};