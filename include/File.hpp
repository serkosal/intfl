#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "Colors.hpp"
#include "Window.hpp"

namespace fs = std::filesystem;

// helper printer function
std::wstring nesting_repr(
    const std::vector<bool>& nesting_map, 
    const std::wstring& filename = L""
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

class File
{
protected:
    fs::path _m_path;
    fs::file_type _m_type;
public:
    fs::file_type get_type() const { return _m_type; }

    virtual void print(
        const Window& win,
        std::vector<bool> nesting_map,

        // these arguments needed for compatibility with
        // Directory::print
        size_t max_depth = 0, 
        size_t max_listing_n = 0
    ) const
    {
        win.print(nesting_repr(nesting_map));
        auto filename = _m_path.filename().wstring() + L'\n';

        if (_m_type == fs::file_type::directory)
            win.print(
                filename, 
                NcursesColors::FS_Directory
            );
        else
            win.printr(
                filename,
                NcursesColors::FS_Regular
            );
    }

    File(const fs::path& path, fs::file_type type);
    ~File();
};

File::File(const fs::path& path, fs::file_type type)
: _m_path{path}, _m_type{type}
{
}

File::~File()
{
}