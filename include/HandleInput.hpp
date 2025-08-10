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
public:

    // std::wstring consume_command()
    // {
    //     auto res = command;
    //     command = L"";

    //     return res;
    // }

    // returns zero on success
    #ifdef USE_N_CURSES
    bool get_command(WINDOW* win, std::wstring& command)
    #else
    bool get_command(std::wstring& command)
    #endif
    {
        command = L"";
        #ifdef USE_N_CURSES

            wint_t wch;
            auto res = wget_wch(win, &wch);
            while (wch != WEOF && wch != L'\n' && wch != L'\r' )
            {
                if (res == KEY_CODE_YES)
                {
                    if (wch == KEY_ENTER || wch == KEY_END)
                    {
                        command = L"";
                        break;
                    }
                    else if (wch == KEY_BACKSPACE && command.size())
                    {
                        command.resize(command.size() - 1);
                        wclear(win);
                        waddwstr(win, command.c_str());
                        wrefresh(win);
                    }
                }
                else if (res == ERR)
                {
                    command = L"";
                    return 1;
                }
                else if (res == OK && !std::iswcntrl(wch))
                {
                    command += static_cast<wchar_t>(wch);
                    wchar_t buf[2] = {static_cast<wchar_t>(wch), L'\0'};
                    waddwstr(win, buf);
                    wrefresh(win);
                }

                res = wget_wch(win, &wch);
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
