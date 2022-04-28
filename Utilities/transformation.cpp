#pragma once
#include <vector>
#include "mathmatrix.h" 
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
    float Y[3];



    translation(point p) {
        this->ps.push_back(p);
        this->time = 0;
        this->align = false;
    }
    translation(vector<point> ps, bool align, float time) {
        this->ps = ps;
        this->align = align;
        this->time = time;
        //initial specification of an YY vector
        this->Y[0] = 0;
        this->Y[1] = 1;
        this->Y[2] = 0;
    }

    //compute CatmullRom point given 4 points and t vlaue
    void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

        // catmull-rom matrix
        float M[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                            { 1.0f, -2.5f,  2.0f, -0.5f},
                            {-0.5f,  0.0f,  0.5f,  0.0f},
                            { 0.0f,  1.0f,  0.0f,  0.0f} };

        // T 
        float T[4] = { t * t * t, t * t, t, 1 };


        //P matrix that contains all componments of P{p0,p1,p2,p3}
        float P[3][4];
        for (int i = 0; i < 3; i++) {
            P[i][0] = p0[i];
            P[i][1] = p1[i];
            P[i][2] = p2[i];
            P[i][3] = p3[i];
        }


        // compute A = M * P
        float A[3][4];
        multMatrixVector((float*)M, P[0], A[0]);
        multMatrixVector((float*)M, P[1], A[1]);
        multMatrixVector((float*)M, P[2], A[2]);


        // compute pos = T * A
        for (int i = 0; i < 3; i++) {
            pos[i] = 0;
            for (int j = 0; j < 4; j++)
                pos[i] += T[j] * A[i][j];
        }

        // compute deriv = dT * A
        float dT[4] = { 3 * t * t, 2 * t, 1, 0 };
        for (int i = 0; i < 3; i++) {
            deriv[i] = 0;
            for (int j = 0; j < 4; j++)
                deriv[i] += dT[j] * A[i][j];
        }
    }

    // given  global t, returns the point in the curve (guião 8)
    void getGlobalCatmullRomPoint(float glt, vector<point> ps, float* pos, float* deriv) {

        int POINT_COUNT = ps.size();
        float t = glt * POINT_COUNT; // this is the real global t
        int index = floor(t);  // which segment
        t = t - index; // where within  the segment

        // indices store the points
        int indices[4];
        indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
        indices[1] = (indices[0] + 1) % POINT_COUNT;
        indices[2] = (indices[1] + 1) % POINT_COUNT;
        indices[3] = (indices[2] + 1) % POINT_COUNT;

        float p[4][3];

        for (int i = 0; i < 4; i++) {
            p[i][0] = ps[indices[i]].getX();
            p[i][1] = ps[indices[i]].getY();
            p[i][2] = ps[indices[i]].getZ();
        }

        getCatmullRomPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
    }

    void transform() {
        if(ps.size() < 4){
            point p = ps[0];
            glTranslatef(p.getX(), p.getY(), p.getZ());
        }
        else {
            //point in the curve
            float res[3];
            //vector tangent to the curve
            float deriv[3];

            float glt = glutGet(GLUT_ELAPSED_TIME) / (this->time * 1000);
            
            //render the curve
            glColor3f(1, 1, 1);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 100; i++) {
                getGlobalCatmullRomPoint(i/100.0f, ps, res, deriv);
                glVertex3fv(res);
            }
            glEnd();

            //animation without align to the curve
            if(this->align){
                getGlobalCatmullRomPoint(glt,ps,res,deriv);
                glTranslatef(res[0], res[1], res[2]);

                //Xi = p'(t)
                //deriv = X
                     
                //Zi = Xi * Yi-1
                float Z[3]; 
                cross(deriv,Y,Z);
                //Yi = Zi * Xi
                cross(Z,deriv,Y);

                //all vectors have to be normalized
                normalize(deriv);
                normalize(Y);
                normalize(Z);

                //OpenGL matrices are column major => so it's used the transpose of the rotation instead
                float rotationMatrix[16];
                buildRotationMatrix(deriv,Y,Z,rotationMatrix);

                glMultMatrixf(rotationMatrix);
            }else{
                //animation without align to the curve
                 getGlobalCatmullRomPoint(glt,ps,res,deriv);
                 glTranslatef(res[0], res[1], res[2]);
            }
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