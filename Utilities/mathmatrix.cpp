#include "mathmatrix.h"
void multMatrixVector(float* m, float* v, float* res) {

        for (int j = 0; j < 4; ++j) {
            res[j] = 0;
            for (int k = 0; k < 4; ++k) {
                res[j] += v[k] * m[j * 4 + k];
            }
        }
    }

void cross(float* a, float* b, float* res) {
    res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float* a) {

	    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        if(l!=0){
            a[0] = a[0] / l;
	        a[1] = a[1] / l;
	        a[2] = a[2] / l;
        }

	   
}

void buildRotationMatrix(float * deriv,float * YY,float * ZZ,float * rotationMatrix){
    rotationMatrix[0] = deriv[0]; rotationMatrix[1] = deriv[1]; rotationMatrix[2] = deriv[2]; rotationMatrix[3] = 0;
	rotationMatrix[4] = YY[0]; rotationMatrix[5] = YY[1]; rotationMatrix[6] = YY[2]; rotationMatrix[7] = 0;
	rotationMatrix[8] = ZZ[0]; rotationMatrix[9] = ZZ[1]; rotationMatrix[10] = ZZ[2]; rotationMatrix[11] = 0;
	rotationMatrix[12] = 0; rotationMatrix[13] = 0; rotationMatrix[14] = 0; rotationMatrix[15] = 1;

}