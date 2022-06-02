#pragma once
#include <string>
#include <regex>
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
		try {
			//						x					y				z				nx			        ny				  nz				tx				 ty
			regex str_expr("^[+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)?\\s*$");
			if (std::regex_match(point, str_expr)) {
				float values[8] = {0,0,0,0,0,0,0,0};
				string delimiter = " ";

				size_t pos = 0;
				string token;
				int i = 0;
				while ((pos = point.find(delimiter)) != string::npos) {
					token = point.substr(0, pos);
					values[i] = stof(token);
					point.erase(0, pos + delimiter.length());
					i += 1;
				}
				this->x = values[0];
				this->y = values[1];
				this->z = values[2];

			}
		}
		catch (regex_error e) {
			cout << e.what();
		}
		catch (...)
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