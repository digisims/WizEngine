#ifndef WIZSOUNDCONTROLLER_H
#define WIZSOUNDCONTROLLER_H

class wizSoundController
{
    public:

    wizSoundController();
    virtual ~wizSoundController();

    virtual void update(float _dt) = 0;

    protected:

};

#endif // WIZSOUNDCONTROLLER_H
