/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include <iostream>

namespace ZNN
{
namespace UTIL
{

template<class floatType>
std::vector<floatType> addVectors (const std::vector<floatType>& vec1, const std::vector<floatType>& vec2) {
    std::vector<floatType> temp;
    temp.resize (vec2.size());
    for (size_t i = 0; i < vec2.size(); i++)
        temp[i] = vec2[i] + vec1 [i];    
    return temp;
}

template<class floatType>
std::vector<floatType> multiplyVectors (const std::vector<floatType>& vec1, const std::vector<floatType>& vec2) {
    std::vector<floatType> temp;
    temp.resize (vec2.size());
    for (size_t i = 0; i < vec2.size(); i++)
        temp[i] = vec2[i] * vec1 [i];    
    return temp;
}

} // namespace UTIL
} // namespace ZNN