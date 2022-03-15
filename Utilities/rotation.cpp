#include "point.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class rotation {
private:
    float angle;
    float x;
    float y;
    float z;

public:
    rotation() {
        this->angle = 0;
        this->x = 0;
        this->y = 0;
        this->z = 0;

    }
    rotation(float angle, float x, float y, float z) {
        this->angle = angle;
        this->x = x;
        this->y = y;
        this->z = z;
    }



    void rotate() {
        glRotatef(this->angle, this->x, this->y, this->z);
    }

    void desrotate() {
        glRotatef(-this->angle, this->x, this->y, this->z);
    }


};