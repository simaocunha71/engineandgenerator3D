#pragma once
#include <string>
#include <functional>
using namespace std;

class Point {
private:
	float x;
	float y;
	float z;
public:
	Point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
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