#include "Directory.hpp"

#include <iterator>
#include <string>

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

std::vector<FilePrintRepr> Directory::to_repr(
    const NestingMap& nesting_map, 
    size_t max_depth, 
    size_t max_listing_n
) const
{
    std::vector<FilePrintRepr> res;

    if (nesting_map.size() > max_depth) 
        return res;

    for (const auto& el : File::to_repr(nesting_map, 0, 0))
        res.push_back(el);

    if (isCollapsed)
        return res;

    size_t counter = 0;

    for (auto it = children.begin(); it != children.end(); ++it)
    {
        auto new_nesting_map = nesting_map;

        if (++counter > max_listing_n)
        {
            new_nesting_map.arr().push_back(false);

            res.push_back(FilePrintRepr(
                new_nesting_map, it->second.get(), children.size() - max_listing_n 
            ));
            
            return res;
        }

        new_nesting_map.arr().push_back(std::next(it) != children.end());
        auto new_entries = it->second->to_repr(
            new_nesting_map, 
            max_depth,
            max_listing_n
        );

        for (const auto& el : new_entries)
            res.push_back(el);
    }

    return res;
}
