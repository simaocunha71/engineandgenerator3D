#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include <stdlib.h>

int write_point(float x, float y, float z, FILE* fname);

//para teste
void write_glTriangle(FILE* file);
void write_glEnd(FILE* file);

#endif