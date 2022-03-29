#include "../Utilities/models.cpp" 
#include <string>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <map>
#include "tinyxml2/tinyxml2.h"
#include "../Utilities/camera.cpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace tinyxml2;
using namespace std;

float _x = 0.0f;
float _y = 0.0f;
float _z = 0.0f;
float _anglex = 0.0f;
float _angley = 0.0f;
float _anglez = 0.0f;

camera cam = camera();
models mods = models();

GLenum mode = GL_LINE;

GLuint vertices, verticeCount;


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
	gluPerspective(cam.fov,
		ratio, //aspect
		cam.near,
		cam.far);

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

	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, verticeCount);

	// End of frame
	glutSwapBuffers();
}

void keyboardfunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		_x += 0.1;
		glutPostRedisplay();
		break;
	case 'd':
		_x -= 0.1;
		glutPostRedisplay();
		break;
	case 'r':
		_z += 0.1;
		glutPostRedisplay();
		break;
	case 'f':
		_z -= 0.1;
		glutPostRedisplay();
		break;
	case 'w':
		_y += 0.1;
		glutPostRedisplay();
		break;
	case 's':
		_y -= 0.1;
		glutPostRedisplay();
		break;
	case 'g':
		_anglex += 2.0;
		glutPostRedisplay();
		break;
	case 'j':
		_anglex -= 2.0;
		glutPostRedisplay();
		break;
	case 'y':
		_angley += 2.0;
		glutPostRedisplay();
		break;
	case 'h':
		_angley -= 2.0;
		glutPostRedisplay();
		break;
	case 'i':
		_anglez += 2.0;
		glutPostRedisplay();
		break;
	case 'k':
		_anglez -= 2.0;
		glutPostRedisplay();
		break;
	case 'm':
		if (mode == GL_LINE) mode = GL_FILL;
		else mode = GL_LINE;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void prepare_data() {
	vector<float> vertexB;


	vertexB.push_back(-1.0f);
	vertexB.push_back(1.0f);
	vertexB.push_back(0.0f);

	vertexB.push_back(0.0f);
	vertexB.push_back(0.0f);
	vertexB.push_back(0.0f);

	vertexB.push_back(1.0f);
	vertexB.push_back(1.0f);
	vertexB.push_back(0.0f);

	verticeCount = vertexB.size() / 3;
	glGenBuffers(1, &vertices);


	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * vertexB.size(), // tamanho do vector em bytes
		vertexB.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)
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


	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardfunc);

	// init GLEW
#ifndef __APPLE__
	glewInit();
#endif

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	printf("Preparing data...\n");
	//mods.prepare_data();

	prepare_data();
	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}



int main(int argc, char** argv) {
	/*
	if (argc == 2) {
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
			printf("XML needs a field called \"world\"");
			return -1;
		}

		//camera est� no inicio do xml
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
				printf("WARNING: \"position\" (element of \"camera\") not detected. Using default values...");
			}
			XMLElement* lookAt_e = camera_e->FirstChildElement("lookAt");
			if (lookAt_e) {
				lookAt_e->QueryAttribute("x", &cam.lx);
				lookAt_e->QueryAttribute("y", &cam.ly);
				lookAt_e->QueryAttribute("z", &cam.lz);
				printf("<lookAt x=%0.f y=%0.f z=%0.f />\n", cam.lx, cam.ly, cam.lz);
			}
			else {
				printf("WARNING: \"lookAt\" (element of \"camera\") not detected. Using default values...");
			}
			XMLElement* up_e = camera_e->FirstChildElement("up");
			if (up_e) {
				up_e->QueryAttribute("x", &cam.ux);
				up_e->QueryAttribute("y", &cam.uy);
				up_e->QueryAttribute("z", &cam.uz);
				printf("<up x=%0.f y=%0.f z=%0.f />\n", cam.ux, cam.uy, cam.uz);
			}
			else {
				printf("WARNING: \"up\" (element of \"camera\") not detected. Using default values...");
			}
			XMLElement* projection_e = camera_e->FirstChildElement("projection");
			if (projection_e) {
				projection_e->QueryAttribute("fov", &cam.fov);
				projection_e->QueryAttribute("near", &cam.near);
				projection_e->QueryAttribute("far", &cam.far);
				printf("<projection fov=%0.f near=%0.f fav=%0.f />\n", cam.fov, cam.near, cam.far);
			}
			else {
				printf("WARNING: \"projection\" (element of \"camera\") not detected. Using default values...");
			}

		}
		else{
			printf("WARNING: \"camera\" not detected. Using default values...");
		}

		XMLElement* group_e = world_e->FirstChildElement("group");
		if (group_e) {
			XMLElement* models_e = group_e->FirstChildElement("models");

			XMLElement* model_e = models_e->FirstChildElement("model");
			while (model_e) {
				model m = model();
				const char* filename = model_e->Attribute("file");
				

				ifstream file(filename);
				if (file.is_open()) { //abre o ficheiro
					printf("Loading file model %s ...\n", filename);
					string line;
					while (getline(file, line)) { //l� linha a linha
						if (line[0] == 'i') {
							int idx = stoi(line.substr(1, line.length()));
							printf("%d->", idx);
							m.add_index(idx); //cada indice corresponde a 3 coords.
						}
						else {
							point p = point(line);
							m.add_point(p);
						}
					}
					file.close();
				}
				else {
					printf("File model %s does not exist!", filename);
				}
				printf("File loaded model %s.\n", filename);
				model_e = model_e->NextSiblingElement("model");
				mods.add_model(m);
			}
		}

	}
	else printf("Invalid arguments!");*/
	
	
	glut_main(argc, argv);

	return 0;
}

