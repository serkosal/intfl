#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <iterator>

#include "File.hpp"

namespace fs = std::filesystem;
using FilePtr = std::unique_ptr<File>;

class Directory : public File
{
private:
    std::map<fs::path, FilePtr> children;
public:
    Directory(const fs::path& path, size_t depth = 0);

    bool exists()
    { return _m_type == fs::file_type::directory; }

    void print(bool is_last = false) override;
    // std::string to_json();

    ~Directory();
};

Directory::Directory(const fs::path& path, size_t depth)
: File(path, fs::file_type::not_found, depth)
{
    if (!fs::exists(path)) return;

    if (fs::is_directory(path))
    {
        _m_type = fs::file_type::directory;

        for (const auto& entry: fs::directory_iterator(path))
        {
            if (fs::is_directory(entry))
                children[entry] = std::make_unique<Directory>(entry, _m_depth + 1);
            else
                children[entry] = std::make_unique<File>(entry, fs::file_type::regular, _m_depth + 1);
        }
    }
}

void Directory::print(bool is_last)
{
    
    File::print(is_last);

    for (auto it = children.cbegin(); it != children.end(); ++it )
    {
        const auto& file = it->second;

        is_last = it == std::prev(children.end());

        it->second->print(is_last);
    }        

}

Directory::~Directory()
{
}
