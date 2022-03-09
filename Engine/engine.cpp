#include "tinyxml2/tinyxml2.h"
#include <string>
#include "stdlib.h"

using namespace tinyxml2;

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
			XMLElement* position = camera->FirstChildElement("position");
			if (position) {
				float px,py,pz;
				position->QueryAttribute("x", &px);
				position->QueryAttribute("y", &py);
				position->QueryAttribute("z", &pz);
				printf("<position x=%0.f y=%0.f z=%0.f />\n", px, py, pz);
			}
			else{
				//erro
			}
			XMLElement* lookAt = camera->FirstChildElement("lookAt");
			if (lookAt) {
				float lx,ly,lz;
				lookAt->QueryAttribute("x", &lx);
				lookAt->QueryAttribute("y", &ly);
				lookAt->QueryAttribute("z", &lz);
				printf("<lookAt x=%0.f y=%0.f z=%0.f />\n", lx, ly, lz);
			}
			else {
				//erro
			}
			XMLElement* up = camera->FirstChildElement("up");
			if (up) {
				float ux, uy, uz;
				up->QueryAttribute("x", &ux);
				up->QueryAttribute("y", &uy);
				up->QueryAttribute("z", &uz);
				printf("<up x=%0.f y=%0.f z=%0.f />\n", ux, uy, uz);
			}
			else {
				//erro
			}
			XMLElement* projection = camera->FirstChildElement("projection");
			if (projection) {
				float fov, near, far;
				projection->QueryAttribute("for", &fov);
				projection->QueryAttribute("near", &near);
				projection->QueryAttribute("far", &far);
				printf("<projection fov=%0.f near=%0.f fav=%0.f />\n", fov, near, far);
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
				printf("<model file=%s />\n",filename);
				model = model->NextSiblingElement("model");
			}
		}

		return 0;
		//printf("%s\n", argv[1]);
		//std::string filename = argv[1];
		//std::string file_format = filename.substr(filename.find(".")+1,filename.length());
		//if (strcmp("xml", file_format.c_str()) == 0) {
			//printf("%s\n", file_format.c_str());
		//}
	}
	else printf("Argumentos inválidos!");

	return 0;
}

