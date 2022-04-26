#pragma once
#include <vector>
#include "point.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif




class transformation {
public:
    virtual void transform() = 0;
};

class translation : public transformation {
public:

    vector<point> ps;
    float time;
    bool align;


    translation(point p) {
        this->ps.push_back(p);
        this->time = 0;
        this->align = false;
    }
    translation(vector<point> ps, bool align, float time) {
        this->ps = ps;
        this->align = align;
        this->time = time;
    }
    void transform() {
        if(ps.size() < 4){
            point p = ps[0];
            glTranslatef(p.getX(), p.getY(), p.getZ());
        }
        else {
            //TODO
        }
    }
};

class rotation : public transformation {
public:

    float time;
    float angle;
    point p;

    rotation(float angle, point p) {
        this->p = p;
        this->angle = angle;
        this->time = 0;
    }
    rotation(point p, float time) {
        this->p = p;
        this->time = time;
        this->angle = 0;
    }
    void transform() {
        if (this->time != 0) {
            glRotatef(this->angle, this->p.getX(), this->p.getY(), this->p.getZ());
        }
        else {
            //TODO
        }
    }
};

class scaling : public transformation{
public:
    point p;

    scaling(point p) {
        this->p = p;
    }
    void transform() {
        glScalef(this->p.getX(), this->p.getY(), this->p.getZ());
    }
};