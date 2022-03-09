#pragma once
#include <string>
#include <functional>
using namespace std;

class point {
private:
	float x;
	float y;
	float z;
public:
	point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	point() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	point(string point) : point() {
		int space_one = 0;
		int space_two = 0;
		while (point.at(space_one) != ' ') {
			space_one++; space_two++;
		}
		space_two++;
		while (point.at(space_two++) != ' ') {
			space_two++;
		}
		this->x = stof(point.substr(0, space_one));
		this->y = stof(point.substr(space_one + 1, space_two));
		this->z = stof(point.substr(space_two + 1, point.length()));
	}

	void setX(float x) {
		this->x = x;
	}
	void setY(float y) {
		this->y = y;
	}
	void setZ(float z) {
		this->z = z;
	}
	float getX() {
		return this->x;
	}
	float getY() {
		return this->y;
	}
	float getZ() {
		return this->z;
	}
	size_t get_hash_code() {
		string point = to_string(x) + " " + to_string(y) + " " + to_string(z);
		return hash<string>()(point);
	}
};