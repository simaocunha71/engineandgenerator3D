#include <stdio.h>
#include <stdlib.h>
#include "box.h"

void write_faceOxz_down(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = -halfsize;
    z = halfsize;
    y = -halfsize;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float az = z - part;            
            
            point p1 = point(x, y, z,0,-1,0,x+ halfsize,z+ halfsize);
            point p2 = point(x, y, az, 0, -1, 0,x+ halfsize,az+ halfsize);
            point p3 = point(ax, y, z, 0, -1, 0,ax+ halfsize,z+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            p1 = point(ax, y, az, 0, -1, 0,ax+ halfsize,az+ halfsize);
            p2 = point(ax, y, z, 0, -1, 0,ax+ halfsize,z+ halfsize);
            p3 = point(x, y, az, 0, -1, 0,x+ halfsize,az+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            z = az;
        }
        x = x + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOxz_up(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = -halfsize;
    z = halfsize;
    y = halfsize;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float az = z - part;
            
            point p1 = point(x, y, az, 0, 1, 0, x+ halfsize,az+ halfsize);
            point p2 = point(x, y, z, 0, 1, 0,x+ halfsize,z+ halfsize);
            point p3 = point(ax, y, z, 0, 1, 0,ax+ halfsize,z+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);

            p1 = point(ax, y, z, 0, 1, 0,ax+ halfsize,z+ halfsize);
            p2 = point(ax, y, az, 0, 1, 0,ax+ halfsize,az+ halfsize);
            p3 = point(x, y, az, 0, 1, 0,x+ halfsize,az+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            z = az;
        }
        x = x + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOyz_front(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = halfsize;
    z = halfsize;
    y = -halfsize;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ay = y + part;
            float az = z - part;
            
            point p1 = point(x, y, z, 1, 0, 0,z+ halfsize,y+ halfsize);
            point p2 = point(x, y, az, 1, 0, 0,az+ halfsize,y+ halfsize);
            point p3 = point(x, ay, z, 1, 0, 0,z+ halfsize,ay+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            p1 = point(x, ay, az, 1, 0, 0,az+ halfsize,ay+ halfsize);
            p2 = point(x, ay, z, 1, 0, 0,z+ halfsize,ay+ halfsize);
            p3 = point(x, y, az, 1, 0, 0,az+ halfsize,y+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            z = az;
        }
        y = y + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOyz_back(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = -halfsize;
    z = halfsize;
    y = -halfsize;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ay = y + part;
            float az = z - part;
            
            point p1 = point(x, y, az, -1, 0, 0, az+ halfsize,y+ halfsize);
            point p2 = point(x, y, z, -1, 0, 0,z+ halfsize,y+ halfsize);
            point p3 = point(x, ay, z, -1, 0, 0,z+ halfsize,ay+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            p1 = point(x, ay, z, -1, 0, 0,z+ halfsize,ay+ halfsize);
            p2 = point(x, ay, az, -1, 0, 0,az+ halfsize,ay+ halfsize);
            p3 = point(x, y, az, -1, 0, 0,az+ halfsize,y+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            z = az;
        }
        y = y + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOxy_back(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = -halfsize;
    z = -halfsize;
    y = halfsize;

    float inity = y;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float ay = y - part;
            
            point p1 = point(x, ay, z, 0, 0, -1,x+ halfsize,ay+ halfsize);
            point p2 = point(x, y, z, 0, 0, -1,x+ halfsize,y+ halfsize);
            point p3 = point(ax, y, z, 0, 0, -1,ax+ halfsize,y+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);

            p1 = point(ax, y, z, 0, 0, -1,ax+ halfsize,y+ halfsize);
            p2 = point(ax, ay, z, 0, 0, -1,ax+ halfsize,ay+ halfsize);
            p3 = point(x, ay, z, 0, 0, -1,x+ halfsize,ay+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            y = ay;
        }
        x = x + part;
        y = inity;
        i1 = i1 + 1;
    }
}

void write_faceOxy_front(float size, int div, points* ps) {
    float x, z, y;

    float halfsize = size / 2;

    x = -halfsize;
    z = halfsize;
    y = halfsize;

    float inity = y;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float ay = y - part;
            
            point p1 = point(x, y, z, 0, 0, 1,x+ halfsize,y+ halfsize);
            point p2 = point(x, ay, z, 0, 0, 1,x+ halfsize,ay+ halfsize);
            point p3 = point(ax, y, z, 0, 0, 1,ax+ halfsize,y+ halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            p1 = point(ax, ay, z, 0, 0, 1,ax+ halfsize,ay+ halfsize);
            p2 = point(ax, y, z, 0, 0, 1,ax+ halfsize,y+ halfsize);
            p3 = point(x, ay, z, 0, 0, 1,x+ halfsize,ay+halfsize);
            ps->add_point(p1);
            ps->add_point(p2);
            ps->add_point(p3);
            
            i2 = i2 + 1;
            y = ay;
        }
        x = x + part;
        y = inity;
        i1 = i1 + 1;
    }
}


int write_box(float size, int div, char* fname) {
    FILE* file = fopen(fname, "w+");
    points ps = points();

    write_faceOxz_down(size, div, &ps);
    write_faceOxz_up(size, div, &ps);
    write_faceOyz_front(size, div, &ps);
    write_faceOyz_back(size, div, &ps);
    write_faceOxy_front(size, div, &ps);
    write_faceOxy_back(size, div, &ps);

    write_points(ps,file);
    fclose(file);
    return 0;
}
