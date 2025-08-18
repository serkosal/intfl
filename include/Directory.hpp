#pragma once

#ifndef INTFL_DIRECTORY_HPP_
#define INTFL_DIRECTORY_HPP_

#include <filesystem>
#include <map>
#include <vector>

#include "File.hpp"
#include "Window.hpp"

namespace intfl
{

/**
 * @brief Contains same data as File class and additional directory specific one
 * 
 */
class Directory : public File
{
private:
    std::map<fs::path, FilePtr> M_children;

    std::vector<FilePrintRepr> toRepr(
        const NestingMap& nesting_map, 
        size_t max_depth, 
        size_t max_listing_n
    ) const override;

    // todo move is_collapsed to Views 
    mutable bool M_is_collapsed = false;
public:

    bool isCollapsed() const override 
    { return M_is_collapsed; }

    const File& collapse() const override
    { 
        M_is_collapsed = true;

        return *this;
    }
    const File& expand() const override
    { 
        M_is_collapsed = true;

        return *this;
    }
    const File& collapseExpand() const override
    {
        M_is_collapsed = !M_is_collapsed; 
        return *this; 
    }


    Directory(const fs::path& path);

    ~Directory() override {}

    bool exists() const 
    {   return M_type == fs::file_type::directory; }

    std::vector<FilePrintRepr> toRepr(
        size_t max_depth = 5, 
        size_t max_listing_n = 15
    ) const
    {
        return Directory::toRepr(
            {NestingMap{}}, max_depth, max_listing_n
        );
    }
};

} // end of the 'intfl' namespace

#endif