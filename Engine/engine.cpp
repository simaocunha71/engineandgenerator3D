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
	points ps;
public:
	model() {
		this->filename = "";
		this->ps = points();
	}
	void add_point(point p) {
		ps.add_point(p);
	}

	void add_triangle_index(string t) {
		ps.add_triangle_index(t);
	}

	void set_filename(string filename) {
		this->filename = filename;
	}
	string get_filename() {
		return this->filename;
	}
	point get_point(int i) {
		return this->ps.get_point(i);
	}
	triangle get_next_triangle() {
		return this->ps.get_next_triangle();
	}

	int get_ntriangles() {
		return ps.get_ntriangles();
	}
};

class models {
private:
	list<model> list_model;
	int nmodels;
public:
	models() {
		this->list_model;
		this->nmodels = 0;
	}
	void add_model(model m) {
		list_model.push_back(m);
		this->nmodels += 1;
	}

	int get_nmodels() {
		return this->nmodels;
	}

	model get_next_model() {
		model m = list_model.front();
		list_model.pop_front();
		this->nmodels -= 1;
		return m;
	}

};

camera cam = camera();
models mods = models();

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(cam.fov, ratio, cam.near, cam.far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// set the camera
	glLoadIdentity();
	gluLookAt(cam.px,cam.py,cam.pz,
			  cam.lx,cam.ly,cam.lz,
		      cam.ux,cam.uy,cam.uz );

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (mods.get_nmodels() > 0) {
		model m = mods.get_next_model();
		while (m.get_ntriangles() > 0) {
			triangle t = m.get_next_triangle();
			t.draw();
		}
	}

	// End of frame
	glutSwapBuffers();
}

int glut_main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG_PROJECT");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}



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
							m.add_triangle_index(line);
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
				mods.add_model(m);
			}
		}

	}
	else printf("Argumentos inválidos!");

	glut_main(argc, argv);

	return 0;
}

