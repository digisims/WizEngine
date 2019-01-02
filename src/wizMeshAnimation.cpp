#include "wizMeshAnimation.h"

wizMeshAnimation::wizMeshAnimation()
{
    loopable = false;
}

void wizMeshAnimation::load(std::fstream& _msh)
{
    unsigned int frames;
    _msh.read((char*)&frames, sizeof(unsigned int));

    for (unsigned int i=0; i<frames; i++)
    {
        wizMeshFrame* frame = new wizMeshFrame(_msh);
        addFrame(frame);
    }
}

void wizMeshAnimation::load(std::ifstream& _msh)
{
    std::string data;

    do
    {
        _msh >> data;

        if (data.compare("FRAME")==0)
         {
            wizMeshFrame* frame = new wizMeshFrame(_msh);

            addFrame(frame);
        }
    }
    while (data.compare("END")!=0);
}

wizMeshAnimation::wizMeshAnimation(std::ifstream& _msh)
{
    loopable = false;
    load(_msh);
}

wizMeshAnimation::wizMeshAnimation(std::fstream& _msh)
{
    loopable = false;
    load(_msh);
}

wizMeshAnimation::~wizMeshAnimation()
{
    for (unsigned int i = 0; i < frameList.size(); i++)
    {
        delete frameList[i];
    }
}

void wizMeshAnimation::addFrame(wizMeshFrame* _frame)
{
    frameList.push_back(_frame);
}

void wizMeshAnimation::removeFrame(int _idx)
{
    frameList.erase(frameList.begin() + _idx);
}

wizMeshFrame* wizMeshAnimation::getFrame(int _idx)
{
    return frameList[_idx];
}

int wizMeshAnimation::getFrameCount()
{
    return frameList.size();
}

void wizMeshAnimation::setLoopable(bool _loopable)
{
    loopable = _loopable;
}

bool wizMeshAnimation::getLoopable()
{
    return loopable;
}
