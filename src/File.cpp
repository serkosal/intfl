#include "File.hpp"

void File::print(
    const Window &win,
    NestingMap nesting_map,

    // these arguments needed for compatibility with
    // Directory::print
    size_t max_depth,
    size_t max_listing_n
) const
{
    win.print(nesting_repr(nesting_map));
    auto filename = _m_path.filename().wstring() + L'\n';

    if (_m_type == fs::file_type::directory)
        win.print(
            filename,
            NcursesColors::FS_Directory);
    else
        win.printr(
            filename,
            NcursesColors::FS_Regular);
}

std::wstring nesting_repr(
    const NestingMap& nesting_map, 
    const std::wstring& filename
)
{
    int sz = nesting_map.size();


    std::wstring res;
    res.reserve(sz * 3);

    for (int lvl = 0; lvl < sz - 1; ++lvl)
    {
        if (nesting_map[lvl])
        {
            #ifdef USE_N_CURSES
                res += L"│   ";
            #else
                res += L"|   ";
            #endif
        }
        else
        {
            #ifdef USE_N_CURSES
                res += L"    "; 
            #else
                res += L"    ";
            #endif
        }   
    }
    
    if (sz)
    {
        if (!nesting_map[sz - 1])
        {
            #ifdef USE_N_CURSES
                res += L"└── ";
            #else
                res += L"|__ ";
            #endif
        }
        else
        {
            #ifdef USE_N_CURSES
                res += L"├── ";
            #else
                res += L"|-- ";
            #endif
        }
    }

    res += filename;

    return res;
}
