#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <stdio.h>


class transformation {
public:
    float angle = 0;
    float x = 0;
    float y = 0;
    float z = 0;
    bool have = false;

    virtual void transform() = 0;
};

class translation : public transformation {
public:
    translation(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->have = true;
    }
    void transform() {
        if (this->have) {
            glTranslatef(this->x, this->y, this->z);
        }
    }
};

class scaling : public transformation{
public:
    scaling(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->have = true;
    }
    void transform() {
        if (this->have) 
            glScalef(this->x, this->y, this->z);
    }
};

class rotation : public transformation {
public:
    rotation(float angle, float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->angle = angle;
        this->have = true;
    }
    void transform() {
        if (this->have) 
            glRotatef(this->angle, this->x, this->y, this->z);
    }
};