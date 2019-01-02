#ifndef WIZMATRIX_H
#define WIZMATRIX_H

#include "wizVector3.h"

class wizMatrix
{
    public:

    static void invert(float* _matrix, float* _result);
    static void scale(float* _matrix, float _scalar);
    static float determinant(float* _matrix);
    static void cross(wizVector3, float* _result);
    static void mul(float* _m1, float* _m2, float* _result);
    static void sub(float* _m1, float* _m2, float* _result);

    protected:

    static int getIndex(int _row, int _column);
};

#endif // WIZMATRIX_H
