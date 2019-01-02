#ifndef WIZMESHANIMATION_H
#define WIZMESHANIMATION_H

#include "wizMeshFrame.h"
#include "wizProgress.h"

#include <vector>
#include <fstream>

class wizMeshAnimation
{
    public:

    wizMeshAnimation();
    wizMeshAnimation(std::ifstream& _msh);
    wizMeshAnimation(std::fstream& _msh);
    virtual ~wizMeshAnimation();

    void addFrame(wizMeshFrame* _frame);
    void removeFrame(int _idx);
    wizMeshFrame* getFrame(int _idx);
    int getFrameCount();
    void setLoopable(bool _loopable);
    bool getLoopable();

    protected:

    void load(std::ifstream& _msh);
    void load(std::fstream& _msh);

    std::vector<wizMeshFrame*> frameList;
    bool loopable;
};

#endif // WIZMESHANIMATION_H
