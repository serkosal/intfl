#pragma once

#ifndef INTFL_TYPES_HPP_
#define INTFL_TYPES_HPP_

#include <vector>
#include <string>
#include <filesystem>

namespace intfl {

#define     NESTING_EMPTY               L"    "
#ifdef USE_N_CURSES
    #define NESTING_VLINE               L"│   "
    #define NESTING_BRANCH_CONTINUE     L"├── "
    #define NESTING_BRANCH_LAST         L"└── "
#else
    #define NESTING_VLINE               L"|   "
    #define NESTING_BRANCH_CONTINUE     L"|-- "
    #define NESTING_BRANCH_LAST         L"|__ "
#endif

namespace fs  = std::filesystem;

/**
 * @brief represents file's nesting hierarchy 
 * 
 * Each element of the array is a boolean flag, indicating whether it's not a 
 * last element at this depth, which equal the current element's index. 
 */
class NestingMap
{
    std::vector<bool> M_arr;
public:

    /**
     * @brief Construct a new default Nesting Map object
     * 
     */
    NestingMap() {}

    /**
     * @brief Construct a new Nesting Map object
     * 
     * @param nesting_map 
     */
    NestingMap(std::vector<bool> nesting_map)
    : M_arr{nesting_map}
    {}

    std::vector<bool>& arr() { return M_arr; }
    size_t size() const { return M_arr.size(); }

    /**
     * @brief get wstring representation of nesting map
     * 
     * @return std::wstring 
     */
    std::wstring toWstr() const
    {
        int sz = M_arr.size();

        std::wstring res;
        res.reserve(sz * 3);

        for (int lvl = 0; lvl < sz - 1; ++lvl)
        {
            if (M_arr[lvl])
            {   res += NESTING_VLINE; }
            else
            {   res += NESTING_EMPTY; }
        }

        if (sz)
        {
            if (!M_arr[sz - 1])
            {   res += NESTING_BRANCH_LAST; }
            else
            {   res += NESTING_BRANCH_CONTINUE; }
        }

        return res;
    }
};

struct Flags
{
    bool all{false},
         dirs_only{false},
         prune{false},
         full_filenames{false},
         user{false},
         group{false},
         size{false},
         disk_usage{false},
         no_colors{false},
         ascii{false},
         help{false};
        
    size_t print_max_depth = 5;
    size_t files_limit = 15;
};

} // end of the 'intfl' namespace

#endif