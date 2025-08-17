#pragma once

#ifndef INTFL_FILE_REPR_PRINTER_HPP_
#define INTFL_FILE_REPR_PRINTER_HPP_

#include "File.hpp"
#include "Window.hpp"

namespace intfl {

/**
 * @brief function to print the FilePrintRepr to a specified window
 * 
 * @param file_repr 
 * @param win 
 */
void printFileRepr(
    const FilePrintRepr& file_repr,
    const Window& win
);

} // end of the 'intfl' namespace

#endif