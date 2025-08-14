#include <FileReprPrinter.hpp>

void printFileRepr(
    const FilePrintRepr& file_repr,
    const Window& win
)
{
    auto nesting_str = file_repr.nesting().to_wstr();
    win.printr(nesting_str);

    if (file_repr.file() == nullptr)
    {
        win.printr(
            L"files skipped: " + std::to_wstring(file_repr.get_rest()),
            NcursesColors::NOTICE
        );

        return;
    }

    auto filename_str = file_repr.file()->filename();

    if (file_repr.file()->get_type() == fs::file_type::directory)
    {
        if (file_repr.file()->is_collapsed())
            filename_str += L" ...";

        win.printr(
            filename_str + L"\n",
            NcursesColors::FS_Directory);
    }
    else
        win.printr(
            filename_str + + L"\n",
            NcursesColors::FS_Regular);
}