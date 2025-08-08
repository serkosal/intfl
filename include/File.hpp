#pragma once

// to tell idiot IntelleSense stop ignoring ncurses block codes
// #define USE_N_CURSES 


#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

#include <filesystem>
#include <vector>
#include <string>

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
        std::vector<bool> nesting_map,

        // these arguments needed for compatibility with
        // Directory::print
        size_t max_depth = 0, 
        size_t max_listing_n = 0
    ) const
    {
        auto nesting_str = nesting_repr(nesting_map);
        auto filename_str = _m_path.filename().wstring() + L'\n';
        #ifdef USE_N_CURSES

            addwstr(nesting_str.c_str());

            bool is_dir = (_m_type == fs::file_type::directory);
            if (is_dir)
                NcursesColors::FS_Directory.on();
                    addwstr(filename_str.c_str());
            if (is_dir)
                NcursesColors::FS_Directory.off();

            refresh();
        #else
            std::wcout << nesting_str << filename_str;
        #endif
            
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