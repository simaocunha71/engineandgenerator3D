#include <stdio.h>
#include <stdlib.h>
#include "plane.h"


int write_plane(float size, int div, char* fname) {
    if (size > 0 && div > 0) {
        points ps = points();
        FILE* file = fopen(fname, "w+");
        float x, z;

        float halfsize = size / 2;

        x = -halfsize;
        z = halfsize;

        float initz = z;
        float part = size / div;

        float i1 = 0;

        while (i1 < div) {
            float i2 = 0;
            while (i2 < div) {
                float ax = x + part;
                float az = z - part;
                //               x   y   z   nx  ny  nz     tx       ty
                point p1 = point(x , 0 , az , 0 , 1 , 0 , (x+halfsize)/size, (az + halfsize)/size);
                point p2 = point(x, 0, z, 0, 1, 0, (x+halfsize)/size, (z + halfsize) / size);
                point p3 = point(ax, 0, z, 0, 1, 0, (ax + halfsize)/size, (z + halfsize)/size);
                ps.add_point(p1);
                ps.add_point(p2);
                ps.add_point(p3);

                p1 = point(ax, 0, z, 0, 1, 0, (ax + halfsize)/size, (z + halfsize)/size);
                p2 = point(ax, 0, az, 0, 1, 0, (ax + halfsize)/size, (az + halfsize)/size);
                p3 = point(x, 0, az, 0, 1, 0, (x + halfsize)/size, (az + halfsize)/size);
                ps.add_point(p1);
                ps.add_point(p2);
                ps.add_point(p3);
                i2 = i2 + 1;
                z = az;
            }
            x = x + part;
            z = initz;
            i1 = i1 + 1;
        }
        write_points(ps, file);
        fclose(file);
    }
    return 0;
}