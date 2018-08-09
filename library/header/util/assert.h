#pragma once
#include <string>
#include <iostream>

namespace ZNN
{

inline void assert(bool isTrue, std::string message)
{
    if (isTrue)
    {
        std::cout << message << std::endl;
        throw 0;
    }
}
} // namespace ZNN