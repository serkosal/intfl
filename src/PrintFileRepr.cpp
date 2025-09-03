#include <FileReprPrinter.hpp>

namespace intfl {

void printFileRepr(
    const FilePrintRepr& A_file_repr,
    const Window& A_win
)
{
    auto nesting_str = A_file_repr.nesting().toWstr();
    A_win.print(nesting_str, true);

    if (A_file_repr.getRest())
    {
        A_win.printNotice(
            L"files skipped: " + std::to_wstring(A_file_repr.getRest()),
            true
        );

        return;
    }
    if (!A_file_repr.file())
    {
        A_win.printNotice(L"file unavailable", true);

        return;
    }

    auto filename_str = A_file_repr.file()->filename();

    if (A_file_repr.file()->getType() == fs::file_type::directory)
    {
        A_win.print(
            filename_str, false, false,
            Colors::fs_directory
        );

        if (A_file_repr.file()->isError())
        {   A_win.printErr(L" error"); }
        else if (A_file_repr.file()->isCollapsed())
        {   
            A_win.print(L" ...", false, false, Colors::fs_directory); 
        }

        A_win.print(L"\n", true, false);
    }
    else
    {
        A_win.print(
            filename_str + + L"\n",
            true
        );
    }
}

} // end of the 'intfl' namespace