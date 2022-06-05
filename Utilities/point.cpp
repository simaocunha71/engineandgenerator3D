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
	float nx;
	float ny;
	float nz;
	float tx;
	float ty;
public:
	point(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->nx = 0.0f;
		this->ny = 0.0f;
		this->nz = 0.0f;
		this->tx = 0.0f;
		this->ty = 0.0f;
	}

	point(float x, float y, float z,float nx,float ny,float nz) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->nx = nx;
		this->ny = ny;
		this->nz = nz;
		this->tx = 0.0f;
		this->ty = 0.0f;
	}

	point(float x, float y, float z, float nx, float ny, float nz, float tx, float ty) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->nx = nx;
		this->ny = ny;
		this->nz = nz;
		this->tx = tx;
		this->ty = ty;
	}

	point() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->nx = 0.0f;
		this->ny = 0.0f;
		this->nz = 0.0f;
		this->tx = 0.0f;
		this->ty = 0.0f;
	}

	point(string point) {
		this->x = this->y = this->z = this->nx = this->ny = this->nz = this->tx = this->ty = 0.0f;
		try {
			//							x					y				z				nx			        ny				  nz				tx				 ty
			regex str_expr_full("^[+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)?\\s*$");
			//							x					y				z				nx			        ny				  nz
			regex str_expr_norm("^[+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)?\\s*$");
			//								x					y				z
			regex str_expr_simple("^[+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)? [+-]?\\d+(.\\d+)?\\s*$");
			if (std::regex_match(point, str_expr_full)) {
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
				token = point.substr(0, pos);
				values[i] = stof(token);

				this->x = values[0];
				this->y = values[1];
				this->z = values[2];
				this->nx = values[3];
				this->ny = values[4];
				this->nz = values[5];
				this->tx = values[6];
				this->ty = values[7];

			}else if (std::regex_match(point, str_expr_norm)) {
				float values[6] = { 0,0,0,0,0,0 };
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
				token = point.substr(0, pos);
				values[i] = stof(token);

				this->x = values[0];
				this->y = values[1];
				this->z = values[2];
				this->nx = values[3];
				this->ny = values[4];
				this->nz = values[5];

			}else if (std::regex_match(point, str_expr_simple)) {
				float values[3] = { 0,0,0 };
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
				token = point.substr(0, pos);
				values[i] = stof(token);
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
	void setNX(float nx) {
		this->nx = nx;
	}
	void setNY(float ny) {
		this->ny = ny;
	}
	void setNZ(float nz) {
		this->nz = nz;
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
	float getNX() {
		return this->nx;
	}
	float getNY() {
		return this->ny;
	}
	float getNZ() {
		return this->nz;
	}
	float getTX() {
		return this->tx;
	}
	float getTY() {
		return this->ty;
	}
	


	size_t get_hash_code() {
		string point = point_to_string();
		return hash<string>()(point);
	}

	string point_to_string() {
		return to_string(this->x) + " " + to_string(this->y) + " " + to_string(this->z) + " " + to_string(this->nx) + " " + to_string(this->ny) + " " + to_string(this->nz)+ " " + to_string(this->tx) + " " + to_string(this->ty);
	}
};