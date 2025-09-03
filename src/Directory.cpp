#include "Directory.hpp"

#include <iterator>
#include <string>

namespace intfl {

/*
    TODO:
    check cases when std::bad_alloc is throwed  
*/
void Directory::init(const fs::path& A_path)
{
    if (!fs::exists(A_path, M_err_code)) 
    {
        M_type = fs::file_type::not_found;
        return; 
    }

    if (fs::is_directory(A_path, M_err_code) && !M_err_code)
    {
        M_type = fs::file_type::directory;

        auto it = fs::directory_iterator(A_path, M_err_code);

        if (!M_err_code)
        {
            for (const auto& entry: it)
            {
                std::error_code err_code;
                if (entry.is_directory(err_code))
                {   
                    M_children[entry] = std::make_unique<Directory>(entry);
                }
                else if (!err_code)
                {   
                    M_children[entry] = std::make_unique<File>(
                                            entry, fs::file_type::regular);
                }
                else
                {
                    M_children[entry] = std::make_unique<File>(
                                            entry, fs::file_type::unknown);}
            }
        }

        return;
    }

    M_type = fs::file_type::unknown;
}

/*
    TODO:
    replace res' container type from "std::vector" to "std::forward_list"

    provide result parameter, which will be mutated instead new containers
    creation, copying 
*/
std::vector<FilePrintRepr> Directory::toRepr(
    const NestingMap& A_nesting_map,
    const Flags& A_flags
) const
{
    std::vector<FilePrintRepr> res;

    if (A_nesting_map.size() > A_flags.print_max_depth) 
    {   return res; }

    for (const auto& el : File::toRepr(A_nesting_map, A_flags)) 
    {   res.push_back(el); }  // push current file to the result array

    if (isCollapsed()) 
    {   return res; }

    size_t visual_counter = 0, counter = 0;
    bool isLimited = false;
    std::vector<File*> filtered;

    // filter childs
    for (auto it = M_children.begin(); it != M_children.end(); ++it)
    {
        const auto& K_path    = it->first;
        auto P_file = it->second.get();

        ++counter;

        // filter according --all flag
        if (!A_flags.all && K_path.filename().wstring().starts_with(L'.')) 
        {   continue; }

        // filter according --dirs-only flag
        if (A_flags.dirs_only && P_file->getType() != fs::file_type::directory)
        {   continue; }

        ++visual_counter;

        // skip if files limit count exceeded
        if (visual_counter == A_flags.files_limit)
        {
            filtered.push_back(P_file);
            isLimited = true;
            break;
        }

        filtered.push_back(P_file);
    }

    if (!filtered.size())
    {   return res; }

    auto new_nesting_map = A_nesting_map;
    new_nesting_map.arr().push_back(true);

    // push all filtered, except last
    // 
    // because displaying of the last one, depends on whether display is limited
    // or not 
    for (int i = 0; i < int(filtered.size()) - 1; ++i)
    {
        auto new_entries = filtered[i]->toRepr(
            new_nesting_map,
            A_flags
        );

        for (const auto& el : new_entries)
        {   res.push_back(el); }
    }

    if (!isLimited)
    {   new_nesting_map.arr().back() = false; }

    auto new_entries = filtered.back()->toRepr(
        new_nesting_map,
        A_flags
    );

    for (const auto& el : new_entries)
    {   res.push_back(el); }


    if (isLimited) 
    {
        new_nesting_map.arr().back() = false;
        res.push_back(
            FilePrintRepr(
                new_nesting_map, 
                filtered.back(), 
                M_children.size() - counter
            )
        );
    }

    return res;
}

} // end of the 'intfl' namespace