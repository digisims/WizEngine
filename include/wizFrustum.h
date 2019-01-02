#ifndef WIZFRUSTUM_H
#define WIZFRUSTUM_H

#include "wizPlane.h"
#include "wizVector3.h"
#include "wizBoundingBox.h"

#include <cstdlib>

class wizFrustum
{
    public:

    static const unsigned int PLANE_LEFT = 0;
    static const unsigned int PLANE_RIGHT = 1;
    static const unsigned int PLANE_TOP = 2;
    static const unsigned int PLANE_BOTTOM = 3;
    static const unsigned int PLANE_NEAR = 4;
    static const unsigned int PLANE_FAR = 5;

    static const unsigned int DEF_INSIDE = 0;
    static const unsigned int DEF_INTERSECT = 1;
    static const unsigned int DEF_OUTSIDE = 2;

    wizFrustum();
    wizFrustum(float _nearZ, float _farZ);
    virtual ~wizFrustum();

    void setNearZ(float _nearZ);
    void setFarZ(float _farZ);
    void setModelViewMatrix(float* _matrix);
    void setProjectionMatrix(float* _matrix);
    float getNearZ();
    float getFarZ();
    float* getModelViewMatrix();
    float* getProjectionMatrix();
    float* getResult();

    void update(float* _modelview, float* _projection);
    unsigned int isPointInside(wizVector3 _point);
    unsigned int isBoxInside(wizBoundingBox _bbox);

    protected:

    float nearZ;
    float farZ;
	wizPlane* plane;
	float* modelview;
	float* projection;
	float* result;
};

#endif // WIZFRUSTUM_H
