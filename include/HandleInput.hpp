#pragma once

#ifndef INTFL_HANDLE_INPUT_HPP_
#define INTFL_HANDLE_INPUT_HPP_

#include <string>
#include <vector>

#include "Window.hpp"
#include "File.hpp"
#include "Directory.hpp"

namespace intfl {

bool getCommand(
    const Window &cmdsWin,
    Window &mainWin,
    const Directory& dir,
    std::vector<FilePrintRepr>& reprs, 
    std::wstring &command
);

} // end of namespace 'intfl'

#endif