#include "File.hpp"

namespace intfl {

std::wstring FilePrintRepr::toWstr() const
{

    auto res = M_nesting_map.toWstr();
    
    if (!M_rest_elements && M_file)
    {   return res + M_file->M_path.filename().wstring(); }
    
    if (M_rest_elements)
    {   res += L"files skipped: " + std::to_wstring(M_rest_elements); }
    else
    {   res += L"file skipped"; }
    
    return res;
}

} // end of the 'intfl' namespace