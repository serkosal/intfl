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

void Directory::print(
    const Window& win,
    const NestingMap& nesting_map, 
    size_t max_depth, 
    size_t max_listing_n
) const
{
    if (nesting_map.size() > max_depth) return;

    if (!isCollapsed)
        File::print(
            win,
            nesting_map, 0, 0
        );

    size_t counter = 0;
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        auto new_nesting_map = nesting_map;

        if (++counter > max_listing_n)
        {
            std::wstring files_skipped = L"files skipped: "; 
            files_skipped += std::to_wstring(children.size() - max_listing_n) + L'\n';

            new_nesting_map.push_back(false);

            win.print(nesting_repr(new_nesting_map));
            win.printr(files_skipped, NcursesColors::NOTICE);
            
            return;
        }

        new_nesting_map.push_back(std::next(it) != children.end());
        it->second->print(
        win,
        new_nesting_map, max_depth, max_listing_n);
    }
}
