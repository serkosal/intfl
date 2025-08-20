#include "HandleInput.hpp"

#include <string>
#include <cwchar>
#include <cwctype>

#include "FileReprPrinter.hpp"

#ifdef USE_N_CURSES
    #include <ncursesw/ncurses.h>
#endif

namespace intfl {


bool getCommand(
    App& app,
    std::vector<FilePrintRepr>& A_reprs, 
    std::wstring& A_command
)
{
    A_command = L"";
    #ifdef USE_N_CURSES
        wint_t wch;
        auto res = app.M_cmdsWin.getWch(&wch);
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
                    app.M_cmdsWin.print(A_command, true, true);
                }
                else if (wch == KEY_UP)
                {
                    app.M_mainWin.scrollY(-1);
                    app.M_mainWin.refresh();
                }
                else if (wch == KEY_DOWN)
                {
                    app.M_mainWin.scrollY(1);
                    app.M_mainWin.refresh();
                }
                else if (
                    wch == KEY_MOUSE && getmouse(&event) == OK 
                    && event.bstate & BUTTON1_CLICKED
                )
                {
                    int y_click = event.y + app.M_mainWin.getYOffset();

                    if (y_click >= 0 && y_click < A_reprs.size())
                    {   
                        auto file = A_reprs[y_click].file();
                        
                        file->collapseExpand();

                        A_reprs = app.getDir().toRepr(app.M_flags);
                        app.M_mainWin.clear();
                        for (const auto& repr : A_reprs)
                        {   printFileRepr(repr, app.M_mainWin); }
                        app.M_mainWin.refresh();
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
                app.M_cmdsWin.print(std::wstring(buf), true);
            }

            res = app.M_cmdsWin.getWch(&wch);
        }

        app.M_cmdsWin.clear();
        app.M_cmdsWin.refresh();

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