/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/

#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace ZNN
{

template<class floatType>
struct Serializer {};

template<>
struct Serializer<float> {
    std::string serialize (const float& value) 
    {
        std::stringstream temp;
        temp << std::setprecision(30) << value;
        return temp.str();
    }
    float deserialize (const std::string& value) 
    {
        std::stringstream stream (value);
        float temp;
        stream >> temp;
        return temp;
    }
};

template<>
struct Serializer<double> {
    std::string serialize (const double& value) 
    {
        std::stringstream temp;
        temp << std::setprecision(30) << value;
        return temp.str();
    }
    double deserialize (const std::string& value) 
    {
        std::stringstream stream (value);
        double temp;
        stream >> temp;
        return temp;
    }
};

template<>
struct Serializer<long double> {
    std::string serialize (const long double& value) 
    {
        std::stringstream temp;
        temp << std::setprecision(50) << value;
        return temp.str();
    }
    long double deserialize (const std::string& value) 
    {
        std::stringstream stream (value);
        long double temp;
        stream >> temp;
        return temp;
    }
};

} // namespace ZNN