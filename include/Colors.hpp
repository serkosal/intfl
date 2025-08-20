#pragma once

#ifndef INTFL_COLORS_HPP_
#define INTFL_COLOR_HPP_

namespace intfl 
{

/**
 * @brief class encapsulating ncurses colors specific methods & data 
 * 
 */
class Colors {
public:

    // TYPES
    
    /**
     * @brief represents NcursesColor pair
     * 
     */
    class Color {
        friend class Colors;

        inline static short MS_last_id {0};

        short M_id;
        short M_fg;
        short M_bg;

        Color(short fg, short bg)
        : M_fg{fg}, M_bg{bg}
        { 
            M_id = ++MS_last_id;
        }

        Color(short fg);

    public:
        short getId() const
        {   return M_id; }
    };

    /**
     * @brief Declaration of Colors, It's like enum
     * 
     */
    static const Color
        notice,
        error,
        fs_regular,
        fs_directory,
        fs_executable;
private:

    inline static bool MS_hasColors = false;

    // array to register colors in init function
    static const Color MS_colors[];

// METHODS
public:

    static bool isColors() { return MS_hasColors; }

    static void init();
};

} // end of the 'intfl' namespace

#endif

