#include <stdio.h>
#include <stdlib.h>
#include "sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

int write_sphere(float radius, int slices, int stacks, char* fname) {
    FILE* file = fopen(fname, "w+");
    points ps = points();

    float alpha = 2 * M_PI / slices;
    float alphay = M_PI / stacks;
    float initial_y = radius;

    int i_slices = 0;
    int j = 0;
    float l_radius = 0;
    float up_radius = 0;
    float alpha_y_l = 0;
    float alpha_y_up = 0;
    while (i_slices < slices) {
        i_slices++;

       
        //stack superior
        float alpha_1 = alpha * (i_slices-1);
        float alpha_2 = alpha * (i_slices);
        float alpha_y = -M_PI / 2 + alphay;
        up_radius = cos(alpha_y) * (radius);
       
        float x_base1 = cos(alpha_1) * (up_radius);
        float z_base1 = sin(alpha_1) * (up_radius);

        float x_base2 = cos(alpha_2) * up_radius;
        float z_base2 = sin(alpha_2) * up_radius;

        float y = sin(alpha_y) * (radius);
        
        
        point p1 = point(x_base1, y, z_base1, x_base1, y, z_base1);
        point p2 = point(x_base2, y, z_base2, x_base2, y, z_base2);
        point p3 = point(0.0f, -radius, 0.0f, 0.0f, -radius, 0.0f);
        ps.add_point(p1);
        ps.add_point(p2);
        ps.add_point(p3);
        
        
        j = 2;
        while (j < stacks) {
            alpha_y_l = -M_PI / 2 + alphay * (j - 1);
            alpha_y_up = -M_PI / 2 + alphay * j;
            l_radius = cos(alpha_y_l) * (radius);
            up_radius = cos(alpha_y_up) * (radius);
    
           //Vertices da parte de baixo do quadrilatero
            float x_face1 = cos(alpha_1) * l_radius;
            float z_face1 = sin(alpha_1) * l_radius;

            float x_face2 = cos(alpha_2) * l_radius;
            float z_face2 = sin(alpha_2) * l_radius;

            float y_face1 = sin(alpha_y_l) * (radius);

            //Vertices da parte de cima do quadrilatero
            float x_face3 = cos(alpha_1) * up_radius;
            float z_face3 = sin(alpha_1) * up_radius;

            float x_face4 = cos(alpha_2) * up_radius;
            float z_face4 = sin(alpha_2) * up_radius;

            float y_face2 = sin(alpha_y_up) * (radius);

            //3 4 1
            p1 = point(x_face1, y_face1, z_face1, x_face1, y_face1, z_face1);
            p2 = point(x_face4, y_face2, z_face4, x_face4, y_face2, z_face4);
            p3 = point(x_face2, y_face1, z_face2, x_face2, y_face1, z_face2);
            ps.add_point(p1);
            ps.add_point(p2);
            ps.add_point(p3);

            //2 1 4
            p1 = point(x_face4, y_face2, z_face4, x_face4, y_face2, z_face4);
            p2 = point(x_face1, y_face1, z_face1, x_face1, y_face1, z_face1);
            p3 = point(x_face3, y_face2, z_face3, x_face3, y_face2, z_face3);
            ps.add_point(p1);
            ps.add_point(p2);
            ps.add_point(p3);
 
            j = j +1;
        }
        

        //stack superior
        l_radius = cos(M_PI / 2 - alphay) * (radius);
        

        x_base1 = cos(alpha_1) * (l_radius);
        z_base1 = sin(alpha_1) * (l_radius);

        x_base2 = cos(alpha_2) * l_radius;
        z_base2 = sin(alpha_2) * l_radius;

        y =  sin(M_PI / 2 - alphay) * (radius);

        
        p1 = point(x_base1, y, z_base1, x_base1, y, z_base1);
        p2 = point(0.0f, radius, 0.0f, 0.0f, radius, 0.0f);
        p3 = point(x_base2, y, z_base2, x_base2, y, z_base2);

        ps.add_point(p1);
        ps.add_point(p2);
        ps.add_point(p3);
    }
        
    write_points(ps, file);
    fclose(file);

    return 0;
}