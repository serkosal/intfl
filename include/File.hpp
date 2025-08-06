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

    size_t   _m_depth;
public:
    size_t get_depth() const { return _m_depth; }

    virtual void print(bool is_last = false);

    File(const fs::path& path, fs::file_type type, size_t depth = 0);
    ~File();
};

void File::print(bool is_last)
{
    for (int i = 1; i < _m_depth; ++i)
        std::cout << "│  ";

    if (_m_depth)
    {
        if (is_last) std::cout << "└──";
        else std::cout << "├──";
    }


    std::cout << _m_path.filename().generic_string() << "\n";
}

File::File(const fs::path& path, fs::file_type type, size_t depth)
: _m_path{path}, _m_type{type}, _m_depth{depth}
{
}

File::~File()
{
}
