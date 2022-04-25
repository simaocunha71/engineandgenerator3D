#pragma once
#include <stdio.h>
#include <point.cpp>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif




class transformation {
public:
    float angle = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    vector<float> ps;
    float time = 0;

    virtual void transform() = 0;
};

class translation : public transformation {
public:
    translation(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void transform() {
            glTranslatef(this->x, this->y, this->z);
    }
};

class rotation : public transformation {
public:
    rotation(float angle, float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->angle = angle;
    }
    void transform() {
            glRotatef(this->angle, this->x, this->y, this->z);
    }
};

class scaling : public transformation{
public:
    scaling(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void transform() {
            glScalef(this->x, this->y, this->z);
    }
};