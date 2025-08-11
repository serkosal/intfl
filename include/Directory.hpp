#pragma once

#include <filesystem>
#include <map>
#include <memory>

#include "File.hpp"
#include "Window.hpp"

class Directory : public File
{
private:
    std::map<fs::path, FilePtr> children;

    void print(
        const Window& win,
        NestingMap nesting_map, 
        size_t max_depth, 
        size_t max_listing_n
    ) const override;

public:
    bool isCollapsed = false;

    Directory(const fs::path& path);

    bool exists() const 
    { return _m_type == fs::file_type::directory; }

    
    void print(
        const Window& win,
        size_t max_depth = 5, 
        size_t max_listing_n = 15
    ) const
    { 
        Directory::print(
            win,
            {}, max_depth, max_listing_n
        ); 
    }
};