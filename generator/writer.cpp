#include "writer.h"

int write_points(points ps, FILE* file) {
    if (file == NULL) {
        printf("Error!");
        return 1;
    }
    ps.write_to_file(file);
    return 0;
}

