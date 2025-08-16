#pragma once

#ifndef INTFL_COMMANDS_HPP_
#define INTFL_COMMANDS_HPP_

#include <vector>

#include "Window.hpp"
#include "FileReprPrinter.hpp"

namespace intfl 
{

void commandHelp(const Window& win);

void redraw(const Window& win, const std::vector<FilePrintRepr>& reprs);

}

#endif