#pragma once

#ifndef INTFL_HANDLE_INPUT_HPP_
#define INTFL_HANDLE_INPUT_HPP_

#include <string>
#include <vector>

#include "Window.hpp"
#include "File.hpp"
#include "Directory.hpp"

namespace intfl {

/**
 * @brief Proccess input, yield the command string and handle some other events
 * 
 * @param cmdsWin window to update current command input
 * @param mainWin main Window, passed to process mouse events signals
 * @param dir     directory, used to update mainWin window
 * @param reprs   array of file representations, used to process mouse events
 * @param command command to be returned to the main loop and be processed there
 * @return true   if any error ocured during handling input
 * @return false  if no errors ocured during handling input
 */
bool getCommand(
    const Window& cmdsWin,
    Window& mainWin,
    const Directory& dir,
    std::vector<FilePrintRepr>& reprs, 
    std::wstring &command
);

} // end of the 'intfl' namespace

#endif