#ifndef WIZPROJECTOR_H
#define WIZPROJECTOR_H

#include "wizCamera3D.h"

class wizProjector
{
    public:

    wizProjector(wizCamera3D* _camera);
    virtual ~wizProjector();

    void update();

    protected:

    wizCamera3D* camera;
    float* tmp;
    float* textureMatrix;
};

#endif // WIZPROJECTOR_H
