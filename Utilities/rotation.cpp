#include "point.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class rotation {
public:
    float angle;
    float x;
    float y;
    float z;
    bool have;

    rotation() {
        this->angle = 0;
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->have = false;

    }
    rotation(float angle, float x, float y, float z) {
        this->angle = angle;
        this->x = x;
        this->y = y;
        this->z = z;
        this->have = true;
    }



    void rotate() {
        if(this->have) glRotatef(this->angle, this->x, this->y, this->z);
    }
};