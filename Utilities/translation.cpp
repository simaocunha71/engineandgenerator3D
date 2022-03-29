#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class translation {
private:
    float x;
    float y;
    float z;
public:
    translation() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    translation(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void translate() {
        glTranslatef(this->x, this->y, this->z);
    }
    void destranslate() {
        glTranslatef(-this->x, -this->y, -this->z);
    }
};