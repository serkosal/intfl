#include "File.hpp"

std::wstring FilePrintRepr::to_wstr() const
{

    auto res = m_nesting_map.to_wstr();
    

    if (m_rest_elements)
        res += L"files skipped: " + std::to_wstring(m_rest_elements);
    else
        res += m_file->_m_path.filename().wstring();

    return res;
}
