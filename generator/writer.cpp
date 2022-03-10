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


void write_points(points ps, FILE* file) {
    map<size_t, point> pointsMap = ps.get_points();
    for (auto& x : pointsMap)
    {
        fprintf(file, "%f %f %f\n", x.second.getX(),x.second.getY(),x.second.getZ());
    }
    int ntriangles = ps.get_ntriangles();
    while (ntriangles > 0) {
        fprintf(file, "%s\n", ps.get_next_triangle_i().to_string().c_str());
        ntriangles -= 1;
    }
}

void write_glTriangle(FILE* file) {
    fprintf(file, "glBegin(GL_TRIANGLES);\n");
}

void write_glEnd(FILE* file) {
    fprintf(file, "glEnd();\n");
}