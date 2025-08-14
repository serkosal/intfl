#pragma once

#include <vector>
#include <string>

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

class NestingMap
{
    std::vector<bool> m_arr;
public:

    NestingMap() {}


    NestingMap(std::vector<bool> nesting_map)
    : m_arr{nesting_map}
    {}

    std::vector<bool>& arr() { return m_arr; }
    size_t size() const { return m_arr.size(); }

    std::wstring to_wstr() const
    {
        int sz = m_arr.size();

        std::wstring res;
        res.reserve(sz * 3);

        for (int lvl = 0; lvl < sz - 1; ++lvl)
        {
            if (m_arr[lvl])
                res += NESTING_VLINE;
            else
                res += NESTING_EMPTY;
        }

        if (sz)
        {
            if (!m_arr[sz - 1])
                res += NESTING_BRANCH_LAST;
            else
                res += NESTING_BRANCH_CONTINUE;
        }

        return res;
    }
};