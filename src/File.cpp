#include "File.hpp"

namespace intfl {

std::wstring FilePrintRepr::to_wstr() const
{

    auto res = M_nesting_map.to_wstr();
    

    if (M_rest_elements)
        res += L"files skipped: " + std::to_wstring(M_rest_elements);
    else
        res += M_file->M_path.filename().wstring();

    return res;
}

}