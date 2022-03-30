#include "rotation.cpp"
#include "translation.cpp"
#include "scaling.cpp"


class transformation {
private:
    scaling sc;
    rotation rt;
    translation tr;
    bool have;
public:
    transformation() {
        this->have = false;
    }

    void add_transformation(translation tr) {
        this->tr = tr;
        this->have = true;
    }

    void add_transformation(rotation rt) {
        this->rt = rt;
        this->have = true;
    }

    void add_transformation(scaling sc){
        this->sc = sc;
        this->have = true;
    }

    void transform() {
        if (this->have) {
            printf("transformation\n");
            glPushMatrix();
            rt.rotate();
            tr.translate();
            sc.scale();
        }
    }

    void distransform() {
        if (this->have) {
            glPopMatrix();
            printf("destransformation\n");
        }
    }

};