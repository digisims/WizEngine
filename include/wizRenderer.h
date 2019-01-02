#ifndef WIZRENDERER_H
#define WIZRENDERER_H

class wizRenderer
{
    public:

    wizRenderer() {}
    virtual ~wizRenderer() {}

    virtual void applyGlobalSettings() = 0;
    virtual void undoGlobalSettings() = 0;

    protected:
};

#endif // WIZRENDERER_H
