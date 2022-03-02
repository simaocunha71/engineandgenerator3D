#include <stdio.h>
#include <stdlib.h>
#include "cone.h"
#define _USE_MATH_DEFINES
#include <math.h>

int writeCone(float radius, float height, int slices, int stacks, char* fname) {
    
    FILE* file = fopen(fname, "w+");
    
    //BASE DO CONE
    float a = 2 * M_PI / slices;
    float inita = a;
    float y = -height / 2;
    float x = radius * cos(a);;
    float z = radius * sin(a);;

    int i = 1;
    while (i <= slices) {
        i = i + 1;
        a = inita * i;
        float ax = radius * cos(a);
        float az = radius * sin(a);
        write_glTriangle(file); //para teste, tirar depois;
        write_point(x, y, z, file);
        write_point(0.0f, y, 0.0f, file);
        write_point(ax, y, az, file);
        write_glEnd(file); //para teste, tirar depois;
        x = ax;
        z = az;
    }

    //FACE DO CONE


    fclose(file);

    return 0;
}