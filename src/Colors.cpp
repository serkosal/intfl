#include "Colors.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#else
    enum {
        COLOR_BLACK,
        COLOR_YELLOW,
        COLOR_RED,
        COLOR_WHITE,
        COLOR_BLUE,
        COLOR_GREEN
    };
#endif

namespace intfl {

    inline Colors::Color::Color(short fg)
    : Color(fg, COLOR_BLACK) 
    {}

    /// @brief static member initialization, define colors here
    const Colors::Color
        Colors::notice        = Color(COLOR_YELLOW),
        Colors::error         = Color(COLOR_RED),
        Colors::fs_regular    = Color(COLOR_WHITE),
        Colors::fs_directory  = Color{COLOR_BLUE},
        Colors::fs_executable = Color{COLOR_GREEN};

    
    void Colors::init()
    {
        /// @brief register colors for initialization here
        const Colors::Color* MS_colors[] = {
            &notice,
            &error,
            &fs_regular,
            &fs_directory,
            &fs_executable
        };

        #ifdef USE_N_CURSES
            MS_hasColors = has_colors();

            if(MS_hasColors)
            {	
                start_color();
                constexpr size_t sz = sizeof(MS_colors) / sizeof(Color);
                for (short i = 0; i < sz; ++i) 
                {
                    init_pair(
                        MS_colors[i]->M_id, 
                        MS_colors[i]->M_fg, 
                        MS_colors[i]->M_bg
                    ); 
                }
            }
        #endif
    }
}