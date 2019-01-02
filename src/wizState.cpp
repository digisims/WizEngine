#include "wizState.h"

wizState::wizState()
{
}

wizState::~wizState()
{
}

int wizState::getState()
{
    return state;
}

void wizState::onStart()
{
    state = wizState::STATE_RUNNING;
}

void wizState::onPause()
{
    state = wizState::STATE_PAUSED;
}

void wizState::onResume()
{
    state = wizState::STATE_RUNNING;
}

void wizState::onStop()
{
    state = wizState::STATE_NEW;
}
