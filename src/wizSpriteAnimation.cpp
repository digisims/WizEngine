#include "wizSpriteAnimation.h"

wizSpriteAnimation::wizSpriteAnimation()
{
}

wizSpriteAnimation::wizSpriteAnimation(std::ifstream& _ssh)
{
    std::string data;

    do
    {
        _ssh >> data;

        if (data.compare("FRAME")==0)
        {
            wizSpriteFrame* frame = new wizSpriteFrame(_ssh);

            addFrame(frame);
        }
    }
    while (data.compare("END")!=0);
}

wizSpriteAnimation::~wizSpriteAnimation()
{
    for (unsigned int i = 0; i < frameList.size(); i++)
    {
        delete frameList[i];
    }
}

void wizSpriteAnimation::addFrame(wizSpriteFrame* _frame)
{
    frameList.push_back(_frame);
}

void wizSpriteAnimation::removeFrame(int _idx)
{
    frameList.erase(frameList.begin() + _idx);
}

wizSpriteFrame* wizSpriteAnimation::getFrame(int _idx)
{
    return frameList[_idx];
}

int wizSpriteAnimation::getFrameCount()
{
    return frameList.size();
}

void wizSpriteAnimation::setLoopable(bool _loopable)
{
    loopable = _loopable;
}

bool wizSpriteAnimation::getLoopable()
{
    return loopable;
}
