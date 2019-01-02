#include "wizUtility.h"

int wizUtility::decode(const std::string* _id, const int* _value, unsigned int _values, std::string _decode)
{
    for (unsigned int i=0; i<_values; i++)
    {
        if (_id[i].compare(_decode)==0)
        {
            return _value[i];
        }
    }

    return -1;
}

std::string wizUtility::intToString(int _x)
{
    std::string r;
    std::stringstream s;
    s << _x;
    r = s.str();
    return r;
}

std::string wizUtility::floatToString(float _x, int _n)
{
    std::string r;
    std::stringstream s;
    s << std::fixed << std::setprecision(_n) << _x;
    r = s.str();
    return r;
}

std::vector<std::string> wizUtility::splitString(std::string _text, char _delimiter)
{
    std::vector<std::string> list;
    std::string token;

    for (unsigned int i=0; i<_text.length(); i++)
    {
        if (_text[i] == _delimiter)
        {
            list.push_back(token);
            token="";
        }
        else
        {
            token+=_text[i];
        }
    }

    if (token.length()>0)
    {
        list.push_back(token);
    }

    return list;
}

int wizUtility::min(int a, int b)
{
    return a < b ? a : b;
}

int wizUtility::max(int a, int b)
{
    return a > b ? a : b;
}

float wizUtility::min(float a, float b)
{
    return a < b ? a : b;
}

float wizUtility::max(float a, float b)
{
    return a > b ? a : b;
}
