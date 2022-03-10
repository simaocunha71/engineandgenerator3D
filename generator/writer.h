#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include "../Utilities/points.cpp"

int write_point(float x, float y, float z, FILE* fname);
void write_points(points ps, FILE* file);


//para teste
void write_glTriangle(FILE* file);
void write_glEnd(FILE* file);

#endif