#ifndef WIZSTATEGROUP_H
#define WIZSTATEGROUP_H

#include "wizState.h"

#include <map>
#include <string>

class wizStateGroup
{
    public:

    wizStateGroup();
    virtual ~wizStateGroup();

    void addState(std::string _id, wizState* _state);
    void removeState(std::string _id);
    void startState(std::string _id);
    void stopState(std::string _id);
    void resumeState(std::string _id);
    void pauseState(std::string _id);

    void loadAll();
    void startAll();
    void stopAll();
    void resumeAll();
    void pauseAll();

    void update(float _dt);

    protected:

    bool containsState(std::string _id);

    std::map<std::string, wizState*> states;
};

#endif // WIZSTATEGROUP_H
