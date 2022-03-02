#include "plane.h"
#include "cone.h"
#include "writer.h"
#include "sphere.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>

/** Plane uses 2 arg (length,divisions,file) */
const int ARGS_PLANE = 3;

/** Plane uses 4 arg (radius,height,slices,stacks,file) */
const int ARGS_CONE = 3;

/** Minimum number of args:*/
const int ARGS_MIN = 4;

int main(int argc, char** argv) {
    //int x = writePlane(1, 3, "teste.txt");
    int x = writeSphere(1, 10, 10, "texteSphere.txt");
    if (argc < ARGS_MIN)
        return 1; //ERRO

    char* model = argv[1];
    
    if (strcmp(model, "plane") == 0 && argc == 1 + ARGS_PLANE) {

        float size = std::stof(argv[1]);
        int div = atoi(argv[2]);
        char* fname = argv[3];
   
        int x = writePlane(size, div, fname);

    }
    else if (strcmp(model, "cone") == 0 && argc == 1 + ARGS_CONE) {

    }
    return 0;
}