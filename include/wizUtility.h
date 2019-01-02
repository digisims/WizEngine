#ifndef WIZUTILITY_H
#define WIZUTILITY_H

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

class wizUtility
{
    public:

    static int decode(const std::string* _id, const int* _value, unsigned int _values, std::string _decode);
    static std::string intToString(int _x);
    static std::string floatToString(float _x, int _n);
    static std::vector<std::string> splitString(std::string _text, char _delimiter);
    static int min(int a, int b);
    static int max(int a, int b);
    static float min(float a, float b);
    static float max(float a, float b);
};

#endif // WIZUTILITY_H
