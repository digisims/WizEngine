#include "wizMatrix.h"

void wizMatrix::invert(float* _matrix, float* _result)
{
    _result[getIndex(0, 0)] = _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 3)] + _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(0, 1)] = _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 3)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(0, 2)] = _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 3)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(0, 3)] = _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 1)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 1)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 2)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 2)] + _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 3)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 3)];
    _result[getIndex(1, 0)] = _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 3)] - _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(1, 1)] = _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 0)] + _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 3)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(1, 2)] = _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 3)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 3)];
    _result[getIndex(1, 3)] = _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 0)] + _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 2)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 2)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 3)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 3)];
    _result[getIndex(2, 0)] = _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 0)] + _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 3)] + _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 3)];
    _result[getIndex(2, 1)] = _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 3)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 3)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 3)];
    _result[getIndex(2, 2)] = _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 0)] + _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 3)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 3)];
    _result[getIndex(2, 3)] = _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 0)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 0)] - _matrix[getIndex(0, 3)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 1)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 3)] * _matrix[getIndex(2, 1)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 3)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 3)];
    _result[getIndex(3, 0)] = _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 2)];
    _result[getIndex(3, 1)] = _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 0)] + _matrix[getIndex(0, 2)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 2)] * _matrix[getIndex(3, 1)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(2, 0)] * _matrix[getIndex(3, 2)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(2, 1)] * _matrix[getIndex(3, 2)];
    _result[getIndex(3, 2)] = _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 0)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(3, 1)] + _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(3, 2)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(3, 2)];
    _result[getIndex(3, 3)] = _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 0)] - _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 0)] + _matrix[getIndex(0, 2)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 1)] - _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 2)] * _matrix[getIndex(2, 1)] - _matrix[getIndex(0, 1)] * _matrix[getIndex(1, 0)] * _matrix[getIndex(2, 2)] + _matrix[getIndex(0, 0)] * _matrix[getIndex(1, 1)] * _matrix[getIndex(2, 2)];

    wizMatrix::scale(_result, 1.0f / wizMatrix::determinant(_result));
}

void wizMatrix::scale(float* _matrix, float _scalar)
{
    for (unsigned int i=0; i<16; i++)
    {
        _matrix[i] *= _scalar;
    }
}

float wizMatrix::determinant(float* _matrix)
{
    float value = _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 0)] - _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 0)] - _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 0)] + _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 0)] +
                  _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 0)] - _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 0)] - _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 1)] + _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 1)] +
                  _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 1)] - _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 1)] - _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 1)] + _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 1)] +
                  _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 2)] - _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 2)] - _matrix[wizMatrix::getIndex(0, 3)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 2)] + _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 3)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 2)] +
                  _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 2)] - _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 3)] * _matrix[wizMatrix::getIndex(3, 2)] - _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 3)] + _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 0)] * _matrix[wizMatrix::getIndex(3, 3)] +
                  _matrix[wizMatrix::getIndex(0, 2)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 3)] - _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 2)] * _matrix[wizMatrix::getIndex(2, 1)] * _matrix[wizMatrix::getIndex(3, 3)] - _matrix[wizMatrix::getIndex(0, 1)] * _matrix[wizMatrix::getIndex(1, 0)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 3)] + _matrix[wizMatrix::getIndex(0, 0)] * _matrix[wizMatrix::getIndex(1, 1)] * _matrix[wizMatrix::getIndex(2, 2)] * _matrix[wizMatrix::getIndex(3, 3)];

    return value;
}

int wizMatrix::getIndex(int _row, int _column)
{
    return _row * 4 + _column;
}

void wizMatrix::mul(float* _m1, float* _m2, float* _result)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            float res = 0;

            for(int k=0; k<4; k++)
                res += _m1[i*4+k] * _m2[k*4+j];

            _result[i*4+j] = res;
        }
    }
}

void wizMatrix::cross(wizVector3 _v, float* _result)
{
    for (unsigned int i=0; i<16; i++) _result[i] = 0;

    _result[1] = -_v.getZ();
    _result[2] = _v.getY();
    _result[4] = _v.getZ();
    _result[6] = -_v.getX();
    _result[8] = -_v.getY();
    _result[9] = _v.getX();
}

void wizMatrix::sub(float* _m1, float* _m2, float* _result)
{
    for (unsigned int i=0; i<16; i++)
    {
        _result[i] = _m1[i] - _m2[i];
    }
}
