#pragma once

#include <vector>

#include "Window.hpp"
#include "FileReprPrinter.hpp"

void command_help(const Window& win);

void redraw(const Window& win, const std::vector<FilePrintRepr>& reprs);