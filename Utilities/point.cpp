#pragma once
#include <string>
#include <iostream>
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

	point(string point) {
		int space_one = 0;
		int space_two = 0;
		while (point[space_one] != ' ') {
			space_one+=1;
			space_two+=1;
		}
		space_two+=1;
		while (point[space_two] != ' ') {
			space_two+=1;
		}

		try
		{
			this->x = stof(point.substr(0, space_one));
			this->y = stof(point.substr(space_one + 1, space_two));
			this->z = stof(point.substr(space_two + 1, point.length()));
		}
		catch(...)
		{
			cerr << "Points cannot be converted to floats.\n";
		}
		
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
		string point = point_to_string();
		return hash<string>()(point);
	}

	string point_to_string() {
		return to_string(this->x) + " " + to_string(this->y) + " " + to_string(this->z);
	}
};