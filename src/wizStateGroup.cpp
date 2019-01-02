#include "wizStateGroup.h"

wizStateGroup::wizStateGroup()
{
}

wizStateGroup::~wizStateGroup()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        delete i->second;
    }
}

void wizStateGroup::addState(std::string _id, wizState* _state)
{
    if (!containsState(_id))
    {
        states[_id] = _state;
    }
}

void wizStateGroup::removeState(std::string _id)
{
    if (containsState(_id))
    {
        if (states[_id]->getState() != wizState::STATE_NEW)
        {
            states[_id]->onStop();
        }

        states.erase(states.find(_id));
    }
}

bool wizStateGroup::containsState(std::string _id)
{
    return states.find(_id) != states.end();
}

void wizStateGroup::startState(std::string _id)
{
    if (containsState(_id))
    {
        states[_id]->onStart();
    }
}

void wizStateGroup::stopState(std::string _id)
{
    if (containsState(_id))
    {
        states[_id]->onStop();
    }
}

void wizStateGroup::resumeState(std::string _id)
{
    if (containsState(_id))
    {
        states[_id]->onResume();
    }
}

void wizStateGroup::pauseState(std::string _id)
{
    if (containsState(_id))
    {
        states[_id]->onPause();
    }
}

void wizStateGroup::loadAll()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        i->second->onLoad();
    }
}

void wizStateGroup::startAll()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        startState(i->first);
    }
}

void wizStateGroup::stopAll()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        stopState(i->first);
    }
}

void wizStateGroup::resumeAll()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        resumeState(i->first);
    }
}

void wizStateGroup::pauseAll()
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        pauseState(i->first);
    }
}

void wizStateGroup::update(float _dt)
{
    std::map<std::string, wizState*>::iterator i;

    for (i = states.begin(); i != states.end(); i++)
    {
        i->second->update(_dt);
    }
}
