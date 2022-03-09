#include "tinyxml2/tinyxml2.h"
#include <string>
#include "stdlib.h"

using namespace tinyxml2;

int main(int argc, char** argv) {
	if (argc == 2) {
		FILE* file = NULL;
		if (argv[1]){
			printf("Loading %s\n", argv[1]);
		}

		XMLDocument doc;
		XMLError err = doc.LoadFile(argv[1]);
			
		if (err) {
			fprintf(stderr, "TINYXML FAILURE! Error code: %d\n", err);
			return err;
		}
		printf("%s", argv[1]);
		//printf("%s\n", argv[1]);
		//std::string filename = argv[1];
		//std::string file_format = filename.substr(filename.find(".")+1,filename.length());
		//if (strcmp("xml", file_format.c_str()) == 0) {
			//printf("%s\n", file_format.c_str());
		//}
	}
	else printf("erro");

	return 0;
}

