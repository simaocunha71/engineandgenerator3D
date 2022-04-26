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
    int current_time;
    float angle;
    float angle_time;
    point p;

    rotation(float angle, point p) {
        this->p = p;
        this->angle = angle;
        this->angle_time = 0;
        this->time = 0;
        this->current_time = 0;
    }
    rotation(point p, float time) {
        this->p = p;
        this->time = time;
        this->angle_time = 360 / time;
        this->angle = 0;
        this->current_time = 0;
    }
    void transform() {
        if (this->time != 0) {
            int gluttime = glutGet(GLUT_ELAPSED_TIME); //vem em milisegundos
            int timepassed = gluttime - current_time;
            this->current_time = gluttime;
            float angle_aux = angle_time * timepassed / 1000;
            this->angle += angle_aux;
            
        }
        glRotatef(this->angle, this->p.getX(), this->p.getY(), this->p.getZ());
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