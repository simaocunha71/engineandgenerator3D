#include "writer.h"

int write_point(float x, float y, float z, FILE* file) {
    if (file == NULL) {
        printf("Error!");
        return 1;
    }
    //fprintf(file, "%f, %f, %f\n", x, y, z);
    fprintf(file, "glVertex3f(%f, %f, %f);\n", x, y, z);
    return 0;
}


int write_points(points ps, FILE* file) {
    if (file == NULL) {
        printf("Error!");
        return 1;
    }
    ps.write_map_points(file);
    ps.write_trianglesi(file);
    return 0;
}

void write_glTriangle(FILE* file) {
    fprintf(file, "glBegin(GL_TRIANGLES);\n");
}

void write_glEnd(FILE* file) {
    fprintf(file, "glEnd();\n");
}