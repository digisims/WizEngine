#include "wizFrustum.h"

wizFrustum::wizFrustum()
{
    nearZ = 0.1f;
    farZ = 100.0f;
    plane = new wizPlane[6];
    modelview = new float[16];
    projection = new float[16];
    result = new float[16];
}

wizFrustum::wizFrustum(float _nearZ, float _farZ)
{
    nearZ = _nearZ;
    farZ = _farZ;
    plane = new wizPlane[6];
    modelview = new float[16];
    projection = new float[16];
    result = new float[16];
}

wizFrustum::~wizFrustum()
{
    if (plane!=NULL) delete[] plane;
    if (modelview!=NULL) delete[] modelview;
    if (projection!=NULL) delete[] projection;
    if (result!=NULL) delete[] result;
}

void wizFrustum::setNearZ(float _nearZ)
{
    nearZ = _nearZ;
}

void wizFrustum::setFarZ(float _farZ)
{
    farZ = _farZ;
}

void wizFrustum::setModelViewMatrix(float* _matrix)
{
    modelview = _matrix;
}

void wizFrustum::setProjectionMatrix(float* _matrix)
{
    projection = _matrix;
}

float wizFrustum::getNearZ()
{
    return nearZ;
}

float wizFrustum::getFarZ()
{
    return farZ;
}

float* wizFrustum::getModelViewMatrix()
{
    return modelview;
}

float* wizFrustum::getProjectionMatrix()
{
    return projection;
}

float* wizFrustum::getResult()
{
    return result;
}

void wizFrustum::update(float* _modelview, float* _projection)
{
    modelview = _modelview;
    projection = _projection;

    result[0] = modelview[0] * projection[0] + modelview[1] * projection[4] + modelview[2] * projection[8] + modelview[3] * projection[12];
    result[1] = modelview[0] * projection[1] + modelview[1] * projection[5] + modelview[2] * projection[9] + modelview[3] * projection[13];
    result[2] = modelview[0] * projection[2] + modelview[1] * projection[6] + modelview[2] * projection[10] + modelview[3] * projection[14];
    result[3] = modelview[0] * projection[3] + modelview[1] * projection[7] + modelview[2] * projection[11] + modelview[3] * projection[15];

    result[4] = modelview[4] * projection[0] + modelview[5] * projection[4] + modelview[6] * projection[8] + modelview[7] * projection[12];
    result[5] = modelview[4] * projection[1] + modelview[5] * projection[5] + modelview[6] * projection[9] + modelview[7] * projection[13];
    result[6] = modelview[4] * projection[2] + modelview[5] * projection[6] + modelview[6] * projection[10] + modelview[7] * projection[14];
    result[7] = modelview[4] * projection[3] + modelview[5] * projection[7] + modelview[6] * projection[11] + modelview[7] * projection[15];

    result[8] = modelview[8] * projection[0] + modelview[9] * projection[4] + modelview[10] * projection[8] + modelview[11] * projection[12];
    result[9] = modelview[8] * projection[1] + modelview[9] * projection[5] + modelview[10] * projection[9] + modelview[11] * projection[13];
    result[10] = modelview[8] * projection[2] + modelview[9] * projection[6] + modelview[10] * projection[10] + modelview[11] * projection[14];
    result[11] = modelview[8] * projection[3] + modelview[9] * projection[7] + modelview[10] * projection[11] + modelview[11] * projection[15];

    result[12] = modelview[12] * projection[0] + modelview[13] * projection[4] + modelview[14] * projection[8] + modelview[15] * projection[12];
    result[13] = modelview[12] * projection[1] + modelview[13] * projection[5] + modelview[14] * projection[9] + modelview[15] * projection[13];
    result[14] = modelview[12] * projection[2] + modelview[13] * projection[6] + modelview[14] * projection[10] + modelview[15] * projection[14];
    result[15] = modelview[12] * projection[3] + modelview[13] * projection[7] + modelview[14] * projection[11] + modelview[15] * projection[15];

    plane[PLANE_RIGHT].setX(result[3] - result[0]);
    plane[PLANE_RIGHT].setY(result[7] - result[4]);
    plane[PLANE_RIGHT].setZ(result[11] - result[8]);
    plane[PLANE_RIGHT].setD(result[15] - result[12]);

    plane[PLANE_LEFT].setX(result[3] + result[0]);
    plane[PLANE_LEFT].setY(result[7] + result[4]);
    plane[PLANE_LEFT].setZ(result[11] + result[8]);
    plane[PLANE_LEFT].setD(result[15] + result[12]);

    plane[PLANE_BOTTOM].setX(result[3] + result[1]);
    plane[PLANE_BOTTOM].setY(result[7] + result[5]);
    plane[PLANE_BOTTOM].setZ(result[11] + result[9]);
    plane[PLANE_BOTTOM].setD(result[15] + result[13]);

    plane[PLANE_TOP].setX(result[3] - result[1]);
    plane[PLANE_TOP].setY(result[7] - result[5]);
    plane[PLANE_TOP].setZ(result[11] - result[9]);
    plane[PLANE_TOP].setD(result[15] - result[13]);

    plane[PLANE_FAR].setX(result[3] - result[2]);
    plane[PLANE_FAR].setY(result[7] - result[6]);
    plane[PLANE_FAR].setZ(result[11] - result[10]);
    plane[PLANE_FAR].setD(result[15] - result[14]);

    plane[PLANE_NEAR].setX(result[3] + result[2]);
    plane[PLANE_NEAR].setY(result[7] + result[6]);
    plane[PLANE_NEAR].setZ(result[11] + result[10]);
    plane[PLANE_NEAR].setD(result[15] + result[14]);

    for (unsigned int i=0; i<6; i++)
    {
        plane[i]= plane[i].normalize();
    }
}

unsigned int wizFrustum::isPointInside(wizVector3 _point)
{
    unsigned int result = DEF_INSIDE;

    for (unsigned int i=0; i<6; i++)
	{
        if (plane[i].distanceToPoint(_point)<0.001f)
		{
            return DEF_OUTSIDE;
        }
    }

	return result;
}

unsigned int wizFrustum::isBoxInside(wizBoundingBox _bbox)
{
    wizVector3 tmp[8];

    for (unsigned int i=0; i<8; i++)
    {
        tmp[i] = _bbox.getVertex(i);
    }

    unsigned int result = DEF_INSIDE;

    for (unsigned int p = 0; p < 6; p++)
    {
        unsigned int pIn = 0;
        unsigned int pOut = 0;

        for (unsigned int i = 0; i < 8 && (pIn == 0 || pOut == 0); i++)
        {
            if (plane[p].distanceToPoint(tmp[i]) < 0.001f)
            {
                pOut++;
            }
            else
            {
                pIn++;
            }
        }

        if (pIn == 0)
        {
            return DEF_OUTSIDE;
        }
        else if (pOut > 0)
        {
            result = DEF_INTERSECT;
        }
    }

    return result;
}
