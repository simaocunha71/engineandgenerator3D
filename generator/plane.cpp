#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <list>
#include <iostream>
#include "plane.h"


int write_plane(float size, int div, char* fname) {
    if (size > 0 && div > 0) {
        points ps = points();
        FILE* file = fopen(fname, "w+");
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
                float az = z - part;
                
                point p1 = point(x, 0, az);
                point p2 = point(x, 0, z);
                point p3 = point(ax, 0, z);
                ps.add_triangle_points(p1, p2, p3);

                point p4 = point(ax, 0, z);
                point p5 = point(ax, 0, az);
                point p6 = point(x, 0, az);
                ps.add_triangle_points(p4, p5, p6);
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