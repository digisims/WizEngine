#ifndef WIZSPRITEANIMATION_H
#define WIZSPRITEANIMATION_H

#include "wizUtility.h"
#include "wizSpriteFrame.h"

#include <vector>
#include <string>
#include <fstream>

class wizSpriteAnimation
{
    public:

    wizSpriteAnimation();
    wizSpriteAnimation(std::ifstream& _ssh);
    virtual ~wizSpriteAnimation();

    void addFrame(wizSpriteFrame* _frame);
    void removeFrame(int _idx);
    wizSpriteFrame* getFrame(int _idx);
    int getFrameCount();
    void setLoopable(bool _loopable);
    bool getLoopable();

    protected:

    std::vector<wizSpriteFrame*> frameList;
    bool loopable;
};

#endif // WIZSPRITEANIMATION_H
