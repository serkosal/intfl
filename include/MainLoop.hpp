#pragma once

#ifndef INTFL_MAIN_LOOP_HPP_
#define INTFL_MAIN_LOOP_HPP_

#include "Directory.hpp"
#include "Window.hpp"

namespace intfl {

void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
);

}

#endif