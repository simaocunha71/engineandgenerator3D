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
    point p; //ponto unico da transformaçao (caso seja translation/scale/rotation) ou ponto inicial (caso seja rotation)
    vector<point> ps; //lista de pontos [opcional no xml] (caso seja translation, tem de ter no minimo 4 pontos)
    float angle = 0; //opcional rotation/translate
    float time = 0; //opcional rotation (se não houver, há angle)
    bool align = false; //opcional translate

    virtual void transform() = 0;
};

class translation : public transformation {
public:
    translation(point p) {
        this->p = p;
    }
    translation(vector<point> ps, bool align, float time) {
        this->ps = ps;
        this->align = align;
        this->time = time;
    }
    void transform() { //TODO
            glTranslatef(this->p.getX(), this->p.getY(), this->p.getZ());
    }
};

class rotation : public transformation {
public:
    rotation(float angle, point p) {
        this->p = p;
        this->angle = angle;
    }
    rotation(point p, float time) {
        this->p = p;
        this->time = time;
    }
    void transform() {//TODO
            glRotatef(this->angle, this->p.getX(), this->p.getY(), this->p.getZ());
    }
};

class scaling : public transformation{
public:
    scaling(point p) {
        this->p = p;
    }
    void transform() {
            glScalef(this->p.getX(), this->p.getY(), this->p.getZ());
    }
};