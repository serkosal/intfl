#pragma once

#include "Window.hpp"
#include "File.hpp"
#include "Directory.hpp"

bool get_command(
    const Window &cmdsWin,
    Window &mainWin,
    const Directory& dir,
    std::vector<FilePrintRepr>& reprs, 
    std::wstring &command
);
