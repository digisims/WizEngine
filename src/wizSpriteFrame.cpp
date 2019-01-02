#include "wizSpriteFrame.h"

wizSpriteFrame::wizSpriteFrame()
{
}

wizSpriteFrame::wizSpriteFrame(std::ifstream& _ssh)
{
    std::string data;
    std::vector<std::string> tokens;

    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;
    float aw = 0;
    float ah = 0;

    do
    {
        _ssh >> data;

        tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("TIMING")==0)
            {
                time = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("X")==0)
            {
                x = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("Y")==0)
            {
                y = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("W")==0)
            {
                w = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("H")==0)
            {
                h = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("AW")==0)
            {
                aw = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("AH")==0)
            {
                ah = atof(tokens[1].c_str());
            }
        }
    }
    while (data.compare("END")!=0);

    setSize(wizVector2(w, h));
    setActualSize(wizVector2(aw, ah));
    setPosition(wizVector2(x, y));
}

wizSpriteFrame::~wizSpriteFrame()
{
}

void wizSpriteFrame::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizSpriteFrame::setSize(wizVector2 _size)
{
    size = _size;
}

void wizSpriteFrame::setActualSize(wizVector2 _size)
{
    actualSize = _size;
}

void wizSpriteFrame::setTime(float _time)
{
    time = _time;
}

wizVector2 wizSpriteFrame::getPosition()
{
    return position;
}

wizVector2 wizSpriteFrame::getSize()
{
    return size;
}

wizVector2 wizSpriteFrame::getActualSize()
{
    return actualSize;
}

float wizSpriteFrame::getTime()
{
    return time;
}
