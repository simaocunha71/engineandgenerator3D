#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class scaling {
public:
    float x;
    float y;
    float z;
    bool have;
    scaling() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->have = false;
    }
    scaling(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->have = true;
    }
    void scale() {
        if (this->have) glScalef(this->x, this->y, this->z);
    }
};