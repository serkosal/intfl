#pragma once

#ifdef USE_N_CURSES
    #include <ncurses.h>
#else
    #include <iostream>
#endif

#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// helper printer function
std::string nesting_repr(
    const std::vector<bool>& nesting_map, 
    const std::string& filename = ""
)
{
    int sz = nesting_map.size();


    std::string res;
    res.reserve(sz * 3);

    for (int lvl = 0; lvl < sz - 1; ++lvl)
    {
        if (nesting_map[lvl])
            res += "│   ";
        else
            res += "    "; 
    }
    
    if (sz)
    {
        if (!nesting_map[sz - 1]) res += "└── ";
        else res += "├── ";
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
    )
    {
        auto fileStr = nesting_repr(nesting_map, _m_path.filename().string());
        #ifdef USE_N_CURSES
            printw("%s\n", fileStr.c_str());
            refresh();
        #else
            std::cout << fileStr << "\n";
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