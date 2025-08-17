#include "HandleInput.hpp"

#include <string>
#include <cwchar>
#include <cwctype>

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#endif

#include "Colors.hpp"
#include "File.hpp"
#include "Commands.hpp"

namespace intfl {

bool getCommand(
    const Window& A_cmdsWin, 
    Window& A_mainWin,
    const Directory& A_dir,
    std::vector<FilePrintRepr>& A_reprs, 
    std::wstring& A_command
)
{
    A_command = L"";
    #ifdef USE_N_CURSES
        wint_t wch;
        auto res = wget_wch(A_cmdsWin.getPtr(), &wch);
        MEVENT event;


        while (wch != WEOF && wch != L'\n' && wch != L'\r')
        {
            if (res == KEY_CODE_YES)
            {
                if (wch == KEY_ENTER || wch == KEY_END)
                {
                    A_command = L"";
                    break;
                }
                else if (wch == KEY_BACKSPACE && A_command.size())
                {
                    A_command.resize(A_command.size() - 1);
                    A_cmdsWin.printcr(A_command);
                }
                else if (wch == KEY_UP)
                {
                    A_mainWin.scrollY(-1);
                    A_mainWin.refresh();
                }
                else if (wch == KEY_DOWN)
                {
                    A_mainWin.scrollY(1);
                    A_mainWin.refresh();
                }
                else if (
                    wch == KEY_MOUSE && getmouse(&event) == OK 
                    && event.bstate & BUTTON1_CLICKED
                )
                {
                    int y_click = event.y + A_mainWin.getYOffset();

                    if (y_click >= 0 && y_click < A_reprs.size())
                    {   
                        auto file = A_reprs[y_click].file();
                        
                        file->collapseExpand();

                        A_reprs = A_dir.toRepr();
                        redraw(A_mainWin, A_reprs);
                    }
                        

                    
                }
            }
            else if (res == ERR)
            {
                A_command = L"";
                return 1;
            }
            else if (res == OK && !std::iswcntrl(wch))
            {
                A_command += static_cast<wchar_t>(wch);
                wchar_t buf[2] = {static_cast<wchar_t>(wch), L'\0'};
                A_cmdsWin.printr(std::wstring(buf));
            }

            res = wget_wch(A_cmdsWin.getPtr(), &wch);
        }

        A_cmdsWin.clear();
        A_cmdsWin.refresh();

        return 0;
    #else
        auto &res = std::getline(std::wcin, A_command);
        if (res.fail())
        {   return 1; }
        else
        {   return 0; }

    #endif

    return 1;
}

} // end of the 'intfl' namespace