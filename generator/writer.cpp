#include "writer.h"

int write_points(points ps, FILE* file) {
    if (file == NULL) {
        printf("Error!");
        return 1;
    }
    ps.write_map_points(file);
    ps.write_trianglesi(file);
    return 0;
}

