#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include "File.hpp"
#include "Window.hpp"

class Directory : public File
{
private:
    std::map<fs::path, FilePtr> children;

    std::vector<FilePrintRepr> to_repr(
        const NestingMap& nesting_map, 
        size_t max_depth, 
        size_t max_listing_n
    ) const override;
public:
    bool isCollapsed = false;

    Directory(const fs::path& path);

    bool exists() const 
    { return _m_type == fs::file_type::directory; }

    std::vector<FilePrintRepr> to_repr(
        size_t max_depth = 5, 
        size_t max_listing_n = 15
    ) const
    {
        return Directory::to_repr(
            {NestingMap()}, max_depth, max_listing_n
        );
    }
};