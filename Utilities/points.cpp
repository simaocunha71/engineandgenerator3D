#include "point.cpp"
#include <map>
#include <list>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

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

	string to_string() {
		return "i"+ std::to_string(i1) + " " + std::to_string(i2) + " " + std::to_string(i3);
	}
};


class points {
private:
	
	map<size_t, point> map_points;
	list<triangle_i> triangles;
	int ntriangles;
public:
	points() {
		this->map_points;
		this->triangles;
		this->ntriangles = 0;
	}
	void add_triangle_points(point p1, point p2, point p3) {
		ntriangles += 1;
		add_point(p1);
		add_point(p2);
		add_point(p3);
		triangle_i t = triangle_i(p1.get_hash_code(), p2.get_hash_code(), p3.get_hash_code());
		triangles.push_back(t);
	}

	void add_point(point p) {
		map_points.insert(make_pair(p.get_hash_code(), p));
	}

	void add_triangle_index(string indexs) { //recebe string do tipo "i%d %d %d"
		int space_one = 0;
		int space_two = 0;
		while (indexs[space_one] != ' ') {
			space_one += 1;
			space_two += 1;
		}
		space_two += 1;
		while (indexs[space_two] != ' ') {
			space_two += 1;
		}

		//TODO: try e catch caso as substrings nao sejam convertiveis para float
		size_t i1 = stoi(indexs.substr(1, space_one));
		size_t i2 = stoi(indexs.substr(space_one + 1, space_two));
		size_t i3 = stoi(indexs.substr(space_two + 1, indexs.length()));
		triangle_i t = triangle_i(i1,i2,i3);
		triangles.push_back(t);
	}

	point get_point(size_t i) {
		return map_points.at(i);
	}

	map<size_t, point> get_points() {
		return map_points;
	}

	triangle get_next_triangle() {
		ntriangles -= 1;
		triangle_i ti = triangles.front();
		triangles.pop_front();
		return triangle(get_point(ti.i1), get_point(ti.i2), get_point(ti.i3));
	}

	triangle_i get_next_triangle_i() {
		ntriangles -= 1;
		triangle_i ti = triangles.front();
		triangles.pop_front();
		return ti;
	}

	int get_ntriangles() {
		return this->ntriangles;
	}
};