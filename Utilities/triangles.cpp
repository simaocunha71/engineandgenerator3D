#include "point.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



class triangle {
private:
	point p1;
	point p2;
	point p3;
public:
	triangle(point p1, point p2, point p3) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}

	void draw() {
		glBegin(GL_TRIANGLES);
		glVertex3f(p1.getX(), p1.getY(), p1.getZ());
		glVertex3f(p2.getX(), p2.getY(), p2.getZ());
		glVertex3f(p3.getX(), p3.getY(), p3.getZ());
		glEnd();
	}
};

class triangle_i {
public:
	size_t i1;
	size_t i2;
	size_t i3;
	triangle_i(size_t i1, size_t i2, size_t i3) {
		this->i1 = i1;
		this->i2 = i2;
		this->i3 = i3;
	}

	triangle_i() {
		this->i1 = 0;
		this->i2 = 0;
		this->i3 = 0;
	}

	string to_string() {
		return "i" + std::to_string(i1) + " " + std::to_string(i2) + " " + std::to_string(i3);
	}
};
