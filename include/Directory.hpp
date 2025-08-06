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
    Directory(const fs::path& path);

    bool exists() const 
    { return _m_type == fs::file_type::directory; }

    void print(std::vector<bool> nesting_map = {}) override;
    // std::string to_json();

    ~Directory();
};

Directory::Directory(const fs::path& path)
: File(path, fs::file_type::not_found)
{
    if (!fs::exists(path)) return;

    if (fs::is_directory(path))
    {
        _m_type = fs::file_type::directory;

        for (const auto& entry: fs::directory_iterator(path))
        {
            if (fs::is_directory(entry))
                children[entry] = std::make_unique<Directory>(entry);
            else
                children[entry] = std::make_unique<File>(entry, fs::file_type::regular);
        }
    }
}

void Directory::print(std::vector<bool> nesting_map)
{
    File::print(nesting_map);

    for (auto it = children.begin(); it != children.end(); ++it)
    {
        auto new_nesting_map = nesting_map;
        new_nesting_map.push_back(std::next(it) != children.end());

        it->second->print(new_nesting_map);
    }

}

Directory::~Directory()
{
}
