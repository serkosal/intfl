#pragma once

#include "Window.hpp"
#include "File.hpp"

bool get_command(
    const Window &cmdsWin,
    Window &mainWin,
    const std::vector<FilePrintRepr>& reprs,
    std::wstring &command
);
