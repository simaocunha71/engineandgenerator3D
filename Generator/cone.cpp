#include <stdio.h>
#include <stdlib.h>
#include "cone.h"
#define _USE_MATH_DEFINES
#include <math.h>

int write_cone(float radius, float height, int slices, int stacks, char* fname) {
    
    FILE* file = fopen(fname, "w+");
    points ps = points();
   
    float initial_alpha = 2 * M_PI / slices;
    float radius_div = radius / stacks;
    float height_div = height / stacks;
    float initial_y = - height / 2;

    int i_slices = 1;
    // cada iteraçao desenha uma slice [ou seja, no final de cada itereçao, temos um triangulo da base e uma "face" do cone ligada a este]
    while (i_slices <= slices) {
        i_slices = i_slices + 1;
        float alpha_1 = initial_alpha * (i_slices - 1);
        float alpha_2 = initial_alpha * i_slices;

        float x_base1 = cos(alpha_1) * radius;
        float z_base1 = sin(alpha_1) * radius;

        float x_base2 = cos(alpha_2) * radius;
        float z_base2 = sin(alpha_2) * radius;
        
        point p1 = point(x_base1, initial_y, z_base1);
        point p2 = point(x_base2, initial_y, z_base2);
        point p3 = point(0.0f, initial_y, 0.0f);

        ps.add_point(p1);
        ps.add_point(p2);
        ps.add_point(p3);
        

        int i_stacks = 1;

        //cada iteraçao desenha uma stack de uma slice [ou seja, no final temos uma "face" do cone ligada à base]
        while (i_stacks < stacks) {

            //à medida que subimos na face do cone, o raio diminui.

            //Vertices da parte de baixo do quadrilatero
            float x_face1 = cos(alpha_1) * (radius - radius_div * (i_stacks - 1));
            float z_face1 = sin(alpha_1) * (radius - radius_div * (i_stacks - 1));

            float x_face2 = cos(alpha_2) * (radius - radius_div * (i_stacks - 1));
            float z_face2 = sin(alpha_2) * (radius - radius_div * (i_stacks - 1));

            float y_face1 = initial_y + height_div * (i_stacks - 1);

            //Vertices da parte de cima do quadrilatero
            float x_face3 = cos(alpha_1) * (radius - radius_div * i_stacks);
            float z_face3 = sin(alpha_1) * (radius - radius_div * i_stacks);

            float x_face4 = cos(alpha_2) * (radius - radius_div * i_stacks);
            float z_face4 = sin(alpha_2) * (radius - radius_div * i_stacks);

            float y_face2 = initial_y + height_div * i_stacks;

            
            p1 = point(x_face1, y_face1, z_face1);
            p2 = point(x_face4, y_face2, z_face4);
            p3 = point(x_face2, y_face1, z_face2);
            ps.add_point(p1);
            ps.add_point(p2);
            ps.add_point(p3);

            p1 = point(x_face4, y_face2, z_face4);
            p2 = point(x_face1, y_face1, z_face1);
            p3 = point(x_face3, y_face2, z_face3);
            ps.add_point(p1);
            ps.add_point(p2);
            ps.add_point(p3);
            


            //na ultima iteração da face, não tem que desenhar um quadrilatero (2 triangulos), mas sim, apenas 1.
            if (i_stacks == stacks - 1) {
                
                p1 = point(x_face3, y_face2, z_face3);
                p2 = point(0.0f, -initial_y, 0.0f);
                p3 = point(x_face4, y_face2, z_face4);
                ps.add_point(p1);
                ps.add_point(p2);
                ps.add_point(p3);

                
            }
            i_stacks = i_stacks + 1;
        }
    }   

    write_points(ps, file);
    fclose(file);

    return 0;
}