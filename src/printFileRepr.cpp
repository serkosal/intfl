#include <FileReprPrinter.hpp>

namespace intfl {

void printFileRepr(
    const FilePrintRepr& A_file_repr,
    const Window& A_win
)
{
    auto nesting_str = A_file_repr.nesting().to_wstr();
    A_win.printr(nesting_str);

    if (A_file_repr.file() == nullptr)
    {
        A_win.printr(
            L"files skipped: " + std::to_wstring(A_file_repr.get_rest()),
            NcursesColors::notice
        );

        return;
    }

    auto filename_str = A_file_repr.file()->filename();

    if (A_file_repr.file()->getType() == fs::file_type::directory)
    {
        if (A_file_repr.file()->isCollapsed())
            filename_str += L" ...";

        A_win.printr(
            filename_str + L"\n",
            NcursesColors::fs_directory);
    }
    else
        A_win.printr(
            filename_str + + L"\n",
            NcursesColors::fs_regular);
}

}