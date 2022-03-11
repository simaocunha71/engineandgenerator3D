#include "point.cpp"
#include <map>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

#define INIT_BUFFER_TRIANGLES 100

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
		return "i"+ std::to_string(i1) + " " + std::to_string(i2) + " " + std::to_string(i3);
	}
};


class points {
private:
	map<size_t, point> map_points;
	triangle_i* triangles;
	int ntriangles;
	size_t buffer;
public:
	points() {
		this->map_points;
		this->buffer = INIT_BUFFER_TRIANGLES;
		this->triangles = new triangle_i[this->buffer];
		this->ntriangles = 0;
	}
	void add_triangle_points(point p1, point p2, point p3) {
		add_point(p1);
		add_point(p2);
		add_point(p3);
		triangle_i t = triangle_i(p1.get_hash_code(), p2.get_hash_code(), p3.get_hash_code());
		triangles[ntriangles] = t;
		ntriangles += 1;
		if (ntriangles >= this->buffer) { //se exceder o buffer atual -> 
			size_t new_buffer = this->buffer * 2; // duplica-o -> 
			triangle_i* new_triangles = new triangle_i[new_buffer]; // cria um novo "array" com o tamanho novo -> 
			memcpy(new_triangles, triangles, this->buffer * sizeof(triangle_i)); // copia as cenas do antigo para o novo -> 
			this->buffer = new_buffer; 
			delete[] this->triangles; // deita fora o "array".
			this->triangles = new_triangles;
		}
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

		try{
			size_t i1 = stoll(indexs.substr(1, space_one));
			size_t i2 = stoll(indexs.substr(space_one + 1, space_two));
			size_t i3 = stoll(indexs.substr(space_two + 1, indexs.length()));
			triangle_i t = triangle_i(i1, i2, i3);
			triangles[ntriangles] = t;
			ntriangles += 1;
			if (ntriangles >= this->buffer) { //se exceder o buffer atual -> 
				size_t new_buffer = this->buffer * 2; // duplica-o -> 
				triangle_i* new_triangles = new triangle_i[new_buffer]; // cria um novo "array" com o tamanho novo -> 
				memcpy(new_triangles, triangles, this->buffer * sizeof(triangle_i)); // copia as cenas do antigo para o novo -> 
				this->buffer = new_buffer;
				delete[] this->triangles; // deita fora o "array".
				this->triangles = new_triangles;
			}
		}
		catch(...)
		{
			cerr << "Invalid index\n";;
		}
	}

	point get_point(size_t i) {
		return map_points.at(i);
	}

	map<size_t, point> get_points() {
		return map_points;
	}

	void draw_triangles() {
		for (int i = 0; i < ntriangles; i++) {
			triangle(get_point(triangles[i].i1), get_point(triangles[i].i2), get_point(triangles[i].i3)).draw();
		}
	}

	void write_trianglesi(FILE* file) {
		for (int i = 0; i < ntriangles; i++) {
			fprintf(file, "%s\n", triangles[i].to_string().c_str());
		}
	}

	void write_map_points(FILE* file) {
		for (auto& x : this->map_points)
		{
			fprintf(file, "%f %f %f\n", x.second.getX(), x.second.getY(), x.second.getZ());
		}
	}
};