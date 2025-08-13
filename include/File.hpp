#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "Types.hpp"

class File;

namespace fs = std::filesystem;
using FilePtr = std::unique_ptr<File>;

// flatened linear print-ready representation of file structure
class FilePrintRepr
{
private:
    NestingMap m_nesting_map;
    const File* m_file = nullptr;

    size_t m_rest_elements; // if files skipped
public:

    FilePrintRepr(
        const NestingMap& nesting_map, 
        const File* file = nullptr,
        size_t n_rest_elements = 0
    )
    : m_file(file), 
    m_nesting_map(nesting_map),
    m_rest_elements(n_rest_elements)
    {}

    const File* const file() const
    { return m_file; }


    size_t get_rest() const
    { return m_rest_elements; }

    const NestingMap& nesting() const
    { return m_nesting_map; }

    std::wstring to_wstr() const;

    ~FilePrintRepr() {}
};


class File
{
friend class FilePrintRepr;
friend class NestingMap;
protected:
    fs::path _m_path;
    fs::file_type _m_type;
public:
    fs::file_type get_type() const { return _m_type; }

    virtual std::vector<FilePrintRepr> to_repr(
        const NestingMap& nesting_map,

        // these arguments needed for compatibility with
        // Directory::print
        size_t max_depth = 0, 
        size_t max_listing_n = 0
    ) const
    {
        return {FilePrintRepr(nesting_map, this)};
    }

    std::wstring filename() const
    { return _m_path.filename().wstring(); }

    File(const fs::path& path, fs::file_type type)
    : _m_path{path}, _m_type{type}
    {}
};
