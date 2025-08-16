#pragma once

#ifndef INTFL_FILE_REPR_PRINTER_HPP_
#define INTFL_FILE_REPR_PRINTER_HPP_

#include "File.hpp"
#include "Window.hpp"

namespace intfl {

void printFileRepr(
    const FilePrintRepr& file_repr,
    const Window& win
);

}

#endif