#include "Directory.hpp"

#include <iterator>
#include <string>

#include "Types.hpp"

namespace intfl {

void Directory::init(const fs::path& A_path)
{
    if (!fs::exists(A_path)) 
    { 
        M_type = fs::file_type::not_found;
        return; 
    }

    if (fs::is_directory(A_path))
    {
        M_type = fs::file_type::directory;

        for (const auto& entry: fs::directory_iterator(A_path))
        {
            if (fs::is_directory(entry))
            {   M_children[entry] = std::make_unique<Directory>(entry); }
            else
            {   M_children[entry] = std::make_unique<File>(
                                        entry, fs::file_type::regular);
            }
        }
    }
}

std::vector<FilePrintRepr> Directory::toRepr(
    const NestingMap& A_nesting_map,
    const Flags& A_flags
) const
{
    std::vector<FilePrintRepr> res;

    if (A_nesting_map.size() > A_flags.print_max_depth) 
    {   return res; }

    for (const auto& el : File::toRepr(A_nesting_map, A_flags)) 
    {   res.push_back(el); }

    if (isCollapsed()) 
    {   return res; }

    size_t counter = 0;

    for (auto it = M_children.begin(); it != M_children.end(); ++it)
    {
        const auto& K_path    = it->first;
        const auto& K_file  = it->second; 

        // skip files started from .
        if (!A_flags.all && K_path.filename().wstring().starts_with(L'.')) 
        {   continue; }

        if (A_flags.dirs_only && K_file->getType() != fs::file_type::directory)
        {   continue; }

        auto new_nesting_map = A_nesting_map;

        if (++counter > A_flags.files_limit)
        {
            new_nesting_map.arr().push_back(false);

            res.push_back(FilePrintRepr(
                new_nesting_map, K_file.get(), 
                M_children.size() -  A_flags.files_limit 
            ));
            
            return res;
        }

        const bool is_last = std::next(it) != M_children.end();
        new_nesting_map.arr().push_back(is_last);

        auto new_entries = K_file->toRepr(
            new_nesting_map, 
            A_flags
        );

        for (const auto& el : new_entries)
        {   res.push_back(el); }
    }

    return res;
}

} // end of the 'intfl' namespace