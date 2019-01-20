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
        temp << value;
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
        temp << value;
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
        temp << value;
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

template<>
struct Serializer<int> {
    std::string serialize (const int& value) 
    {
        std::stringstream temp;
        temp << value;
        return temp.str();
    }
    int deserialize (const std::string& value) 
    {
        std::stringstream stream (value);
        int temp;
        stream >> temp;
        return temp;
    }
};

template<>
struct Serializer<unsigned int> {
    std::string serialize (const unsigned int& value) 
    {
        std::stringstream temp;
        temp << value;
        return temp.str();
    }
    unsigned int deserialize (const std::string& value) 
    {
        std::stringstream stream (value);
        unsigned int temp;
        stream >> temp;
        return temp;
    }
};

} // namespace ZNN