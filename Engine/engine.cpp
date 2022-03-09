#include <string>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <map>
#include "tinyxml2/tinyxml2.h"
#include "../Utilities/points.cpp" 
#include "../Utilities/point.cpp"

using namespace tinyxml2;
using namespace std;

class camera {
public:
	float px, py, pz, lx, ly, lz, ux, uy, uz, fov, near, far;
	camera() {
		this->px = 0.0f;
		this->py = 0.0f;
		this->pz = 0.0f;
		this->lx = 0.0f;
		this->ly = 0.0f;
		this->lz = 0.0f;
		this->ux = 0.0f;
		this->uy = 0.0f;
		this->uz = 0.0f;
		this->fov = 0.0f;
		this->near = 0.0f;
		this->far = 0.0f;
	}
};

class model {       
private:             
	string filename;
	points points;
public:
	model() {
		this->filename = "";
		this->points;
	}
	void add_point(point p) {
		points.add_point(p);
	}

	void add_triangle_index(string t) {
		points.add_triangle_index(t);
	}

	void set_filename(string filename) {
		this->filename = filename;
	}
	string get_filename() {
		return this->filename;
	}
	point get_point(int i) {
		return this->points.get_point(i);
	}
	triangle get_next_point() {
		return this->points.get_next_triangle();
	}
};

class models {
private:
	list<model> list_model;
public:
	models() {
		this->list_model;
	}
	void add_model(model m) {
		list_model.push_back(m);
	}
};

camera cam = camera();
models mods = models();

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
		XMLElement* world_e = doc.FirstChildElement("world");
		if (!world_e) {
			//TODO: erro
		}

		//camera está no inicio do xml
		XMLElement* camera_e = world_e->FirstChildElement("camera");
		if (camera_e) {
			XMLElement* position_e = camera_e->FirstChildElement("position");
			if (position_e) {
				position_e->QueryAttribute("x", &cam.px);
				position_e->QueryAttribute("y", &cam.py);
				position_e->QueryAttribute("z", &cam.pz);
				printf("<position x=%0.f y=%0.f z=%0.f />\n", cam.px, cam.py, cam.pz);
			}
			else {
				//TODO: erro
			}
			XMLElement* lookAt_e = camera_e->FirstChildElement("lookAt");
			if (lookAt_e) {
				lookAt_e->QueryAttribute("x", &cam.lx);
				lookAt_e->QueryAttribute("y", &cam.ly);
				lookAt_e->QueryAttribute("z", &cam.lz);
				printf("<lookAt x=%0.f y=%0.f z=%0.f />\n", cam.lx, cam.ly, cam.lz);
			}
			else {
				//TODO: erro
			}
			XMLElement* up_e = camera_e->FirstChildElement("up");
			if (up_e) {
				up_e->QueryAttribute("x", &cam.ux);
				up_e->QueryAttribute("y", &cam.uy);
				up_e->QueryAttribute("z", &cam.uz);
				printf("<up x=%0.f y=%0.f z=%0.f />\n", cam.ux, cam.uy, cam.uz);
			}
			else {
				//TODO: erro
			}
			XMLElement* projection_e = camera_e->FirstChildElement("projection");
			if (projection_e) {
				projection_e->QueryAttribute("fov", &cam.fov);
				projection_e->QueryAttribute("near", &cam.near);
				projection_e->QueryAttribute("far", &cam.far);
				printf("<projection fov=%0.f near=%0.f fav=%0.f />\n", cam.fov, cam.near, cam.far);
			}
			else {
				//TODO: erro
			}

		}

		XMLElement* group_e = world_e->FirstChildElement("group");
		if (group_e) {
			XMLElement* models_e = group_e->FirstChildElement("models");

			XMLElement* model_e = models_e->FirstChildElement("model");
			while (model_e) {
				model m = model();
				m.set_filename(model_e->Attribute("file"));
				

				ifstream file(m.get_filename());
				if (file.is_open()) { //abre o ficheiro
					printf("loading file model %s ...\n", m.get_filename().c_str());
					string line;
					while (getline(file, line)) { //lê linha a linha
						if (line[0] == 'i') {
							size_t i = atoi(line.substr(1, line.length()).c_str());
							m.add_index(i);
						}
						else {
							point p = point(line);
							m.add_point(p);
						}
					}
					file.close();
				}
				else {
					printf("file model %s does not exist!", m.get_filename().c_str());
				}
				model_e = model_e->NextSiblingElement("model");
			}
		}

	}
	else printf("Argumentos inválidos!");

	return 0;
}

