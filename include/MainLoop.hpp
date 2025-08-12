#pragma once

#include "Directory.hpp"
#include "Window.hpp"


void mainLoop(
    const Directory &dir,
    Window& mainWin,
    Window& cmdsWin,
    int argc, char *argv[]
);