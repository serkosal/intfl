#pragma once

#ifndef INTFL_COMMANDS_HPP_
#define INTFL_COMMANDS_HPP_

#include <vector>

#include "Window.hpp"
#include "FileReprPrinter.hpp"

namespace intfl 
{

/**
 * @brief used to redraw calls
 * 
 * @param win 
 * @param reprs 
 */
void redraw(const Window& win, const std::vector<FilePrintRepr>& reprs);

} // end of the 'intfl' namespace

#endif