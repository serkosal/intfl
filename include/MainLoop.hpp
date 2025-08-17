#pragma once

#ifndef INTFL_MAIN_LOOP_HPP_
#define INTFL_MAIN_LOOP_HPP_

#include "Directory.hpp"
#include "Window.hpp"

namespace intfl {

/**
 * @brief function for managing app's main loop
 * 
 * @param dir       directory variable
 * @param mainWin   window to display main information 
 * @param cmdsWin   window to display current input and commands logs
 * @param argc      argument count passed to the application
 * @param argv      vector containing flags passed to the application
 */
void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
);

} // end of the 'intfl' namespace

#endif