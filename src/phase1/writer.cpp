#include "writer.h"

int write_point(float x, float y, float z, FILE* file) {
    if (file == NULL) {
        printf("Error!");
        return 1;
    }
    
    fprintf(file, "%f, %f, %f\n", x, y, z);
    return 0;
}