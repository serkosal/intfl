#pragma once

#ifndef INTFL_FILE_HPP_
#define INTFL_FILE_HPP_

#include <filesystem>
#include <vector>
#include <string>

#include "Types.hpp"

namespace intfl {

class File;

using FilePtr = std::unique_ptr<File>;

// flatened linear print-ready representation of file structure
/**
 * @brief print-ready representation of file
 * 
 */
class FilePrintRepr
{
private:
    NestingMap M_nesting_map;
    const File* M_file = nullptr;

    size_t M_rest_elements; // if files skipped
public:

    FilePrintRepr(
        const NestingMap& nesting_map, 
        const File* file = nullptr,
        size_t n_rest_elements = 0
    )
    : M_file(file), 
      M_nesting_map(nesting_map),
      M_rest_elements(n_rest_elements)
    {}

    const File* const file() const
    { return M_file; }

    size_t getRest() const
    { return M_rest_elements; }

    const NestingMap& nesting() const
    { return M_nesting_map; }

    std::wstring toWstr() const;

    ~FilePrintRepr() {}
};

/**
 * @brief Contains an information about file such as filename, path, metadata
 * 
 */
class File
{
friend class FilePrintRepr;
friend class NestingMap;
protected:
    fs::path M_path;
    fs::file_type M_type;

    std::error_code M_err_code;
public:
    fs::file_type getType() const { return M_type; }

    virtual std::vector<FilePrintRepr> toRepr(
        const NestingMap& nesting_map,

        // these argument needed for compatibility with
        // Directory::print
        const Flags& A_flags
    ) const
    {
        return {FilePrintRepr(nesting_map, this)};
    }

    bool isError() const { return bool(M_err_code); }

    virtual bool  isCollapsed()          const { return false; }
    virtual const File& collapse()       const { return *this; }
    virtual const File& expand()         const { return *this; }

    virtual const File& collapseExpand() const { return *this; }

    std::wstring filename() const
    { return M_path.filename().wstring(); }

    File()
    : M_type(fs::file_type::unknown)
    {}

    void init(const fs::path& path, fs::file_type type)
    {
        M_path = path;
        M_type = type;
    }

    File(const fs::path& path, fs::file_type type = fs::file_type::unknown)
    : M_path{path}, M_type{type}
    {}

    virtual ~File() {};
};

} // end of the 'intfl' namespace

#endif