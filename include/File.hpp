#pragma once

#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class File
{
protected:
    fs::path _m_path;
    fs::file_type _m_type;
public:
    virtual void print(std::vector<bool> nesting_map);

    File(const fs::path& path, fs::file_type type);
    ~File();
};

void File::print(std::vector<bool> nesting_map)
{
    int sz = nesting_map.size();
    for (int lvl = 0; lvl < sz - 1; ++lvl)
    {
        if (nesting_map[lvl])
            std::cout << "│  ";
        else
            std::cout << "   "; 
    }
    
    if (sz)
    {
        if (!nesting_map[sz - 1]) std::cout << "└──";
        else std::cout << "├──";
    }
    
    std::cout << _m_path.filename().generic_string() << "\n";
}

File::File(const fs::path& path, fs::file_type type)
: _m_path{path}, _m_type{type}
{
}

File::~File()
{
}