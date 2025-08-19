#include "Commands.hpp"

#include "Colors.hpp"

namespace intfl {

void redraw(const Window& win, const std::vector<FilePrintRepr>& reprs)
{
    win.clear();
    for (const auto& repr : reprs)
    {   printFileRepr(repr, win); }
    win.refresh();
}

} // end of the 'intfl' namespace