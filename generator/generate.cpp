#include "plane.h"
#include "cone.h"
#include "writer.h"
#include "sphere.h"
#include "box.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>

using namespace std;

/** Plane uses 3 arg (length,divisions,file) */
const int ARGS_PLANE = 4;

/** Box uses 3 arg (length,divisions,file) */
const int ARGS_BOX = 4;

/** Cone uses 5 arg (radius,height,slices,stacks,file) */
const int ARGS_CONE = 6;

/** Sphere uses 4 arg (radius,slices,stacks,file) */
const int ARGS_SPHERE = 5;

/** Minimum number of args:*/
const int ARGS_MIN = 4;

int main(int argc, char** argv) {
    if (argc < ARGS_MIN) {
        printf("Not enough arguments.\n");
        return 1; //ERRO
    }
    else {
        char* model = argv[1];
        try {
            /** Plane uses 3 arg (length,divisions,file) */
            if (strcmp(model, "plane") == 0 && argc == 1 + ARGS_PLANE) {
                float size = stof(argv[2]);
                int div = stoi(argv[3]);
                char* fname = argv[4];
                int x = write_plane(size, div, fname);
            }
            /** Box uses 3 arg (length,divisions,file) */
            else if (strcmp(model, "box") == 0 && argc == 1 + ARGS_BOX) {
                float size = stof(argv[2]);
                int div = atoi(argv[3]);
                char* fname = argv[4];
                int x = write_box(size, div, fname);
            }
            /** Cone uses 5 arg (radius,height,slices,stacks,file) */
            else if (strcmp(model, "cone") == 0 && argc == 1 + ARGS_CONE) {
                float radius = stof(argv[2]);
                float height = stof(argv[3]);
                int slices = atoi(argv[4]);
                int stacks = atoi(argv[5]);
                char* fname = argv[6];
                int x = write_cone(radius, height, slices, stacks, fname);
            }
            /** Sphere uses 4 arg (radius,slices,stacks,file) */
            else if (strcmp(model, "sphere") == 0 && argc == 1 + ARGS_SPHERE) {
                float radius = stof(argv[2]);
                int slices = atoi(argv[3]);
                int stacks = atoi(argv[4]);
                char* fname = argv[5];
                if ( slices > 2 && stacks > 1) {
                    int x = write_sphere(radius, slices, stacks, fname);
                }
                else {
                    printf("Stacks need to be odd or lower values of slices|stacks")
                }
            }
            else {
                printf("Unknown command\n");
            }
        }
        catch (...) {
            cerr << "Invalid argument.\n";
        }
        return 0;
    }
}