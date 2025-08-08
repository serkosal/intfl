#pragma once

#ifdef USE_N_CURSES
    #include <ncursesw/curses.h>
    #include "Colors.hpp"
#else
    #include <iostream>
#endif

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

    void print(
        std::vector<bool> nesting_map, 
        size_t max_depth, 
        size_t max_listing_n
    ) const override;

public:
    Directory(const fs::path& path);

    bool exists() const 
    { return _m_type == fs::file_type::directory; }

    void print(size_t max_depth = 5, size_t max_listing_n = 15) const
    { 
        Directory::print(
            {}, max_depth, max_listing_n
        ); 
    }
    // std::wstring to_json();

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

void Directory::print(
    std::vector<bool> nesting_map, 
    size_t max_depth, 
    size_t max_listing_n
) const
{
    if (nesting_map.size() > max_depth) return;

    File::print(nesting_map, 0, 0);

    size_t counter = 0;
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        auto new_nesting_map = nesting_map;

        if (++counter > max_listing_n)
        {
            std::wstring files_skipped = L"files skipped: "; 
            files_skipped += std::to_wstring(children.size() - max_listing_n) + L'\n';

            new_nesting_map.push_back(false);
            std::wstring nesting_str = nesting_repr(new_nesting_map);

            #ifdef USE_N_CURSES
                addwstr(nesting_str.c_str());
                
                NcursesColors::NOTICE.on();
                    addwstr(files_skipped.c_str());
                NcursesColors::NOTICE.off();

                refresh();
            #else
                std::wcout << files_skipped;
            #endif
            
            return;
        }

        new_nesting_map.push_back(std::next(it) != children.end());
        it->second->print(new_nesting_map, max_depth, max_listing_n);
    }
}

Directory::~Directory()
{
}
