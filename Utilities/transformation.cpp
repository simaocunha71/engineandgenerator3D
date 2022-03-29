#include "rotation.cpp"
#include "translation.cpp"


class transformation {
private:
    rotation rt;
    translation tr;
public:
    transformation() {
        this->rt = rotation();
        this->tr = translation();
    }

    transformation(rotation rt, translation tr) {
        this->rt = rt;
        this->tr = tr;
    }

    transformation(rotation rt) {
        this->rt = rt;
        this->tr = translation();
    }

    transformation(translation tr) {
        this->rt = rotation();
        this->tr = tr;
    }

    void transform() {
        glPushMatrix();
        rt.rotate();
        tr.translate();
    }

    void destransform() {
        glPopMatrix();
    }

};