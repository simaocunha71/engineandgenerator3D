#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

int writeSphere(float radius, int slices, int stacks, char* fname) {

    FILE* file = fopen(fname, "w+");

    float alpha = 2 * M_PI / slices;
    float height_div = radius * 2/ stacks;
    float radius_div = radius / stacks;
    float initial_y = radius;

    int i_slices = 0;
    int i_stacks = stacks;
    int j = 0;
    float upper_radius = 0;
    float lower_radius = 0;
    float alpha_y_upper = 0;
    float alpha_y_lower = 0;
    while (i_slices < slices) {
        i_slices++;


        //stack superior
        float alpha_1 = alpha * (i_slices-1);
        float alpha_2 = alpha * (i_slices);
        float alpha_y = M_PI / 2 - alpha/2;
        lower_radius = cos(alpha_y) * (radius);
       
        float x_base1 = cos(alpha_1) * (lower_radius);
        float z_base1 = sin(alpha_1) * (lower_radius);

        float x_base2 = cos(alpha_2) * lower_radius;
        float z_base2 = sin(alpha_2) * lower_radius;

        float y = cos(alpha / 2) * (radius);

        write_glTriangle(file); //para teste, tirar depois;
        write_point(x_base1, y, z_base1, file);
        write_point(0.0f, radius, 0.0f, file);
        write_point(x_base2, y, z_base2, file);
        write_glEnd(file); //para teste, tirar depois;

        j = 2;
        while (j < stacks) {
            alpha_y_upper = M_PI / 2 - alpha/2 * (j - 1);
            alpha_y_lower = M_PI / 2 - alpha/2 * j;
            upper_radius = cos(alpha_y_upper) * (radius);
            lower_radius = cos(alpha_y_lower) * (radius);
    
           //Vertices da parte de baixo do quadrilatero
            float x_face1 = cos(alpha_1) * upper_radius;
            float z_face1 = sin(alpha_1) * upper_radius;

            float x_face2 = cos(alpha_2) * upper_radius;
            float z_face2 = sin(alpha_2) * upper_radius;

            float y_face1 = sin(alpha_y_upper) * (radius);

            //Vertices da parte de cima do quadrilatero
            float x_face3 = cos(alpha_1) * lower_radius;
            float z_face3 = sin(alpha_1) * lower_radius;

            float x_face4 = cos(alpha_2) * lower_radius;
            float z_face4 = sin(alpha_2) * lower_radius;

            float y_face2 = sin(alpha_y_lower) * (radius);

            write_glTriangle(file); //para teste, tirar depois;
            write_point(x_face1, y_face1, z_face1, file);
            write_point(x_face3, y_face2, z_face3, file);
            write_point(x_face2, y_face1, z_face2, file);
            write_glEnd(file); //para teste, tirar depois;
            write_glTriangle(file); //para teste, tirar depois;
            write_point(x_face4, y_face2, z_face4, file);
            write_point(x_face2, y_face1, z_face2, file); // pra teste
            write_point(x_face3, y_face2, z_face3, file); // pra teste
            write_glEnd(file); //para teste, tirar depois;
            j = j +1;
        }
        

        //stack superior
        upper_radius = cos(-M_PI / 2 + alpha/2) * (radius);
        

        x_base1 = cos(alpha_1) * (upper_radius);
        z_base1 = sin(alpha_1) * (upper_radius);

        x_base2 = cos(alpha_2) * upper_radius;
        z_base2 = sin(alpha_2) * upper_radius;

        y = - cos(alpha/2) * (radius);

        write_glTriangle(file); //para teste, tirar depois;
        write_point(x_base1, y, z_base1, file);
        write_point(0.0f, -radius, 0.0f, file);
        write_point(x_base2, y, z_base2, file);
        write_glEnd(file); //para teste, tirar depois;
    }
        
    fclose(file);

    return 0;
}