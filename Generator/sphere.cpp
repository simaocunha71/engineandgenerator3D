#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

int writeSphere(float radius, int slices, int stacks, char* fname) {

    FILE* file = fopen(fname, "w+");

    float alpha = 2 * M_PI / slices;
    float div_height = radius / stacks / 2;

    int i = 0;
    while (i < slices) {
        i = i + 1;
        float alpha_1 = alpha * (i - 1);
        float alpha_2 = alpha * i;

        float x_base1 = cos(alpha_1) * radius;
        float z_base1 = sin(alpha_1) * radius;

        float x_base2 = cos(alpha_2) * radius;
        float z_base2 = sin(alpha_2) * radius;

        float y = radius - div_height;

        write_glTriangle(file); //para teste, tirar depois;
        write_point(x_base1, y, z_base1, file);
        write_point(0.0f, radius, 0.0f, file);
        write_point(x_base2, y, z_base2, file);
        write_glEnd(file); //para teste, tirar depois;
    }
        
    fclose(file);

    return 0;
}