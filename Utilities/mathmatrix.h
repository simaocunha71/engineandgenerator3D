#ifndef MATHMATRIX_H
#define MATHMATRIX_H
#include <cmath>
void multMatrixVector(float* m, float* v, float* res);
void cross(float* a, float* b, float* res);
void normalize(float* a);
void buildRotationMatrix(float * deriv,float * YY,float * ZZ,float * rotationMatrix); 
#endif