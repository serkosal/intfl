#pragma once

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include <cstring>
    #include "Colors.hpp"
    #include <cwctype>
    #include <cstddef>
#else
    #include <iostream>
#endif

#include <string>


struct InputHandler
{
    std::wstring command;

    // returns zero on success
    bool get_command()
    {
        #ifdef USE_N_CURSES

            wint_t wch;
            auto res = wget_wch(stdscr, &wch);
            while (wch != WEOF && wch != L'\n' && wch != L'\r' )
            {
                if (res == OK)
                {
                    command += static_cast<wchar_t>(wch);
                    addwstr(&command.back());
                    refresh();
                }
                else if (res == KEY_CODE_YES)
                {
                    if (wch == KEY_ENTER || wch == KEY_END)
                    {
                        command = L"";
                        break;
                    }
                        
                }
                else if (res == ERR)
                {
                    return 1;
                    command = L"";
                }

                res = wget_wch(stdscr, &wch);
            }

            return 0;

        #else
            auto& res = std::getline(std::wcin, command);
            if (res.fail())
                return 1;
            else
                return 0;
            
        #endif


        return 1;
    }
};
