#pragma once

#ifndef INTFL_TYPES_HPP_
#define INTFL_TYPES_HPP_

#include <vector>
#include <string>

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
    std::wstring to_wstr() const
    {
        int sz = M_arr.size();

        std::wstring res;
        res.reserve(sz * 3);

        for (int lvl = 0; lvl < sz - 1; ++lvl)
        {
            if (M_arr[lvl])
                res += NESTING_VLINE;
            else
                res += NESTING_EMPTY;
        }

        if (sz)
        {
            if (!M_arr[sz - 1])
                res += NESTING_BRANCH_LAST;
            else
                res += NESTING_BRANCH_CONTINUE;
        }

        return res;
    }
};

} // end of namespace 'intfl'

#endif