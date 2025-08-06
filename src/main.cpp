#include <iostream>

#include "Directory.hpp"

int main()
{
    Directory dir(".");

    if (!dir.exists())
    {
        std::cerr << "Directory not found!\n";
        return 1;
    }
    
    dir.print();

    return 0;
}
