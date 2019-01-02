#ifndef WIZUIBUTTONEVENT_H
#define WIZUIBUTTONEVENT_H


class wizUIButtonEvent
{
    public:

    wizUIButtonEvent();
    wizUIButtonEvent(unsigned int _button);
    virtual ~wizUIButtonEvent();

    int getButton();

    protected:

    int button;
};

#endif // WIZUIBUTTONEVENT_H
