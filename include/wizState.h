#ifndef WIZSTATE_H
#define WIZSTATE_H

class wizState
{
    public:

    static const int STATE_NEW = 0;
    static const int STATE_RUNNING = 1;
    static const int STATE_PAUSED = 2;

    wizState();
    virtual ~wizState();

    virtual void update(float _dt) = 0;

    virtual void onLoad() = 0;
    virtual void onStart();
    virtual void onPause();
    virtual void onResume();
    virtual void onStop();

    int getState();

    protected:

    int state;
};

#endif // WIZSTATE_H
