#include <stdio.h>
#include <stdlib.h>
#include "plane.h"

int writePlane(float size, int div, char* fname) {
    FILE* file = fopen(fname,"w+");
    float x, z;

    x = -size / 2;
    z = size / 2;

    float initz = z;

    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float az = z + part;
            write_point(x, 0, z, file);
            write_point(x, 0, az, file);
            write_point(ax, 0, z, file);
            write_point(ax, 0, az, file);
            i2 = i2 + 1;
            z = az;
        }
        x = x + part;
        z = initz;
        i1 = i1 + 1;
    }

    fclose(file);
    return 0;
}