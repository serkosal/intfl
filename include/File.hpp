#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "Colors.hpp"
#include "Window.hpp"

class File;

namespace fs = std::filesystem;
using FilePtr = std::unique_ptr<File>;
using NestingMap = std::vector<bool>;


std::wstring nesting_repr(
    const NestingMap& nesting_map, 
    const std::wstring& filename = L""
);

class File
{
protected:
    fs::path _m_path;
    fs::file_type _m_type;
public:
    fs::file_type get_type() const { return _m_type; }

    virtual void print(
        const Window& win,
        const NestingMap& nesting_map,

        // these arguments needed for compatibility with
        // Directory::print
        size_t max_depth = 0, 
        size_t max_listing_n = 0
    ) const;

    File(const fs::path& path, fs::file_type type)
    : _m_path{path}, _m_type{type}
    {}
};
