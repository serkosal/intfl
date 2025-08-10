#pragma once


#include <string>
#include <cwchar>

#include "Colors.hpp"
#include "Window.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
#endif

struct InputHandler
{
public:
    // returns zero on success
    bool get_command(const Window& win, std::wstring& command)
    {
        command = L"";
        #ifdef USE_N_CURSES
            wint_t wch;
            auto res = wget_wch(win.get_ptr(), &wch);

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
                        win.printcr(command);
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
                    win.printr(std::wstring(buf));
                }

                res = wget_wch(win.get_ptr(), &wch);
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
