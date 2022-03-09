#include <string>
#include <fstream>
#include <stdlib.h>
#include <list>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Point {
private:
	float x;
	float y;
	float z;
public:
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	void setZ(int z) {
		this->z = z;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	int getZ() {
		return this->z;
	}
};

class Camera {
public:
	float px, py, pz, lx, ly, lz, ux, uy, uz, fov, near, far;
};

class Model {       
private:             
	string filename;
	list<Point> points;
	list<int> index;
public:
	void add_point(Point p) {
		points.push_back(p);
	}

	void add_index(int i) {
		index.push_back(i);
	}
};

int main(int argc, char** argv) {
	if (argc == 2) {
		FILE* file = fopen("teste.txt","w+");
		if (argv[1]){
			printf("Loading %s\n", argv[1]);
		}

		XMLDocument doc;
		XMLError err = doc.LoadFile(argv[1]);
			
		if (err) {
			fprintf(stderr, "TINYXML FAILURE! Error code: %d\n", err);
			return err;
		}
		
		//world engloba todo o xml
		XMLElement* world = doc.FirstChildElement("world");
		if (!world) {
			//dá erro e return
		}

		//camera está no inicio do xml
		XMLElement* camera = world->FirstChildElement("camera");
		if (camera) {
			Camera cam;
			XMLElement* position = camera->FirstChildElement("position");
			if (position) {
				position->QueryAttribute("x", &cam.px);
				position->QueryAttribute("y", &cam.py);
				position->QueryAttribute("z", &cam.pz);
				printf("<position x=%0.f y=%0.f z=%0.f />\n", cam.px, cam.py, cam.pz);
			}
			else {
				//erro
			}
			XMLElement* lookAt = camera->FirstChildElement("lookAt");
			if (lookAt) {
				lookAt->QueryAttribute("x", &cam.lx);
				lookAt->QueryAttribute("y", &cam.ly);
				lookAt->QueryAttribute("z", &cam.lz);
				printf("<lookAt x=%0.f y=%0.f z=%0.f />\n", cam.lx, cam.ly, cam.lz);
			}
			else {
				//erro
			}
			XMLElement* up = camera->FirstChildElement("up");
			if (up) {
				up->QueryAttribute("x", &cam.ux);
				up->QueryAttribute("y", &cam.uy);
				up->QueryAttribute("z", &cam.uz);
				printf("<up x=%0.f y=%0.f z=%0.f />\n", cam.ux, cam.uy, cam.uz);
			}
			else {
				//erro
			}
			XMLElement* projection = camera->FirstChildElement("projection");
			if (projection) {
				projection->QueryAttribute("fov", &cam.fov);
				projection->QueryAttribute("near", &cam.near);
				projection->QueryAttribute("far", &cam.far);
				printf("<projection fov=%0.f near=%0.f fav=%0.f />\n", cam.fov, cam.near, cam.far);
			}
			else {
				//erro
			}

		}

		XMLElement* group = world->FirstChildElement("group");
		if (group) {
			XMLElement* models = group->FirstChildElement("models");

			XMLElement* model = models->FirstChildElement("model");
			while (model) {
				const char* filename = model->Attribute("file");
				

				ifstream file(filename);
				if (file.is_open()) { //abre o ficheiro
					printf("loading file model %s ...\n", filename);
					string line;
					while (getline(file, line)) { //lê linha a linha
						printf("%s\n", line.c_str());
					}
					file.close();
				}
				else {
					printf("file model %s does not exist!",filename);
				}
				model = model->NextSiblingElement("model");
			}
		}

		return 0;
	}
	else printf("Argumentos inválidos!");

	return 0;
}

