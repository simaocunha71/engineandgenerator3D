#include <stdio.h>
#include <stdlib.h>
#include "box.h"

void write_faceOxz_down(float size, int div, FILE* file) {
    float x, z, y;

    x = -size / 2;
    z = size / 2;
    y = -size / 2;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float az = z - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, y, z, file);
            write_point(x, y, az, file);
            write_point(ax, y, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(ax, y, az, file);
            write_point(ax, y, z, file);
            write_point(x, y, az, file);
            write_glEnd(file); //para teste, tirar depois;
            i2 = i2 + 1;
            z = az;
        }
        x = x + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOxz_up(float size, int div, FILE* file) {
    float x, z, y;

    x = -size / 2;
    z = size / 2;
    y = size / 2;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float az = z - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, y, az, file);
            write_point(x, y, z, file);
            write_point(ax, y, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(ax, y, z, file);
            write_point(ax, y, az, file);
            write_point(x, y, az, file);
            write_glEnd(file); //para teste, tirar depois;
            i2 = i2 + 1;
            z = az;
        }
        x = x + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOyz_front(float size, int div, FILE* file) {
    float x, z, y;

    x = size / 2;
    z = size / 2;
    y = -size / 2;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ay = y + part;
            float az = z - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, y, z, file);
            write_point(x, y, az, file);
            write_point(x, ay, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, ay, az, file);
            write_point(x, ay, z, file);
            write_point(x, y, az, file);
            write_glEnd(file); //para teste, tirar depois;
            i2 = i2 + 1;
            z = az;
        }
        y = y + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOyz_back(float size, int div, FILE* file) {
    float x, z, y;

    x = -size / 2;
    z = size / 2;
    y = -size / 2;

    float initz = z;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ay = y + part;
            float az = z - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, y, az, file);
            write_point(x, y, z, file);
            write_point(x, ay, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, ay, z, file);
            write_point(x, ay, az, file);
            write_point(x, y, az, file);
            write_glEnd(file); //para teste, tirar depois;
            i2 = i2 + 1;
            z = az;
        }
        y = y + part;
        z = initz;
        i1 = i1 + 1;
    }
}

void write_faceOxy_back(float size, int div, FILE* file) {
    float x, z, y;

    x = -size / 2;
    z = -size / 2;
    y = size / 2;

    float inity = y;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float ay = y - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, ay, z, file);
            write_point(x, y, z, file);
            write_point(ax, y, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(ax, y, z, file);
            write_point(ax, ay, z, file);
            write_point(x, ay, z, file);
            write_glEnd(file); //para teste, tirar depois;
            i2 = i2 + 1;
            y = ay;
        }
        x = x + part;
        y = inity;
        i1 = i1 + 1;
    }
}

void write_faceOxy_front(float size, int div, FILE* file) {
    float x, z, y;

    x = -size / 2;
    z = size / 2;
    y = size / 2;

    float inity = y;
    float part = size / div;

    int i1 = 0;

    while (i1 < div) {
        int i2 = 0;
        while (i2 < div) {
            float ax = x + part;
            float ay = y - part;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x, y, z, file);
            write_point(x, ay, z, file);
            write_point(ax, y, z, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(ax, ay, z, file);
            write_point(ax, y, z, file);
            write_point(x, ay, z, file);
            write_glEnd(file); //para teste, tirar depois;
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

    write_faceOxz_down(size, div, file);
    write_faceOxz_up(size, div, file);
    write_faceOyz_front(size, div, file);
    write_faceOyz_back(size, div, file);
    write_faceOxy_front(size, div, file);
    write_faceOxy_back(size, div, file);

    fclose(file);
    return 0;
}
