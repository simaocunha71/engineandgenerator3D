#pragma once
#include <vector>
#include "models.cpp"
using namespace std;

class light {
public:
    virtual void init_light() = 0;
    virtual void render_light() = 0;
};

class lights {
public:
    vector<light*> ls;

    lights(){
    }

    void add_light(light* l) {
        this->ls.push_back(l);
    }

    void init_lights() {
        for (vector<light*>::iterator it = this->ls.begin(); it != this->ls.end(); ++it) {
            (*it)->init_light();
        }
    }

    void render_lights() {
        for (vector<light*>::iterator it = this->ls.begin(); it != this->ls.end(); ++it) {
            (*it)->render_light();
        }
    }
};



class light_point : public light {
public:
    int nl;
    float posx;
    float posy;
    float posz;

    light_point(int nl,float posx, float posy, float posz) {
        this->nl = nl;
        this->posx = posx;
        this->posy = posy;
        this->posz = posz;
    }

    void init_light(){
        float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
        float white[4] = { 1.0, 1.0, 1.0, 1.0 };
        float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        // light colors
        glLightfv(GL_LIGHT0+nl, GL_AMBIENT, dark);
        glLightfv(GL_LIGHT0+nl, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0+nl, GL_SPECULAR, white);
        // controls global ambient light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    }

    void render_light() {
        GLfloat pos[4] = {posx,posy,posz,0};
        glLightfv(GL_LIGHT0 + nl, GL_POSITION, pos);
    }
};

class light_directional : public light {
public:
    int nl;
    float dirx;
    float diry;
    float dirz;

    light_directional(int nl,float dirx, float diry, float dirz) {
        this->nl = nl;
        this->dirx = dirx;
        this->diry = diry;
        this->dirz = dirz;
    }

    void init_light() {
        float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
        float white[4] = { 1.0, 1.0, 1.0, 1.0 };
        float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        // light colors
        glLightfv(GL_LIGHT0 + nl, GL_AMBIENT, dark);
        glLightfv(GL_LIGHT0 + nl, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0 + nl, GL_SPECULAR, white);
        // controls global ambient light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    }
    void render_light() {
        GLfloat dir[4] = {dirx,diry,dirz,1};
        glLightfv(GL_LIGHT0 + nl, GL_POSITION, dir);
    }
};

class light_spotlight : public light {
public:
    int nl;
    float posx;
    float posy;
    float posz;
    float dirx;
    float diry;
    float dirz;
    float cutoff;

    light_spotlight(int nl,float posx, float posy, float posz,float dirx, float diry, float dirz, float cutoff) {
        this->nl = nl;
        this->posx = posx;
        this->posy = posy;
        this->posz = posz;
        this->dirx = dirx;
        this->diry = diry;
        this->dirz = dirz;
        this->cutoff = cutoff;
    }

    void init_light() {
        float dark[4] = { 0.2, 0.2, 0.2, 1.0 };
        float white[4] = { 1.0, 1.0, 1.0, 1.0 };
        float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        // light colors
        glLightfv(GL_LIGHT0 + nl, GL_AMBIENT, dark);
        glLightfv(GL_LIGHT0 + nl, GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0 + nl, GL_SPECULAR, white);
        // controls global ambient light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);
    }
    void render_light() {
        GLfloat pos[4] = { posx,posy,posz,0 };
        GLfloat dir[4] = { dirx,diry,dirz,1 };
        GLfloat c[1] = {cutoff};
        glLightfv(GL_LIGHT0 + nl, GL_POSITION, pos);
        glLightfv(GL_LIGHT0 + nl, GL_SPOT_DIRECTION, dir);
        glLightfv(GL_LIGHT0 + nl, GL_SPOT_CUTOFF, c);
    }
};