#include <FileReprPrinter.hpp>

namespace intfl {

void printFileRepr(
    const FilePrintRepr& A_file_repr,
    const Window& A_win
)
{
    auto nesting_str = A_file_repr.nesting().toWstr();
    A_win.printr(nesting_str);

    if (A_file_repr.getRest())
    {
        A_win.printr(
            L"files skipped: " + std::to_wstring(A_file_repr.getRest()),
            NcursesColors::notice
        );

        return;
    }
    if (!A_file_repr.file())
    {
        A_win.printr(
            L"file unavailable",
            NcursesColors::notice
        );

        return;
    }

    auto filename_str = A_file_repr.file()->filename();

    if (A_file_repr.file()->getType() == fs::file_type::directory)
    {
        if (A_file_repr.file()->isCollapsed())
        {   filename_str += L" ..."; }

        A_win.printr(
            filename_str + L"\n",
            NcursesColors::fs_directory);
    }
    else
    {
        A_win.printr(
            filename_str + + L"\n",
            NcursesColors::fs_regular);
    }
}

} // end of the 'intfl' namespace