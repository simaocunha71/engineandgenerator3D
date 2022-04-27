#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
#include<cstring>
using namespace std;
#include "bezier.h"
#include "writer.h"

//Matrix M
float M[4][4] = {{-1.0f,3.0f,-3.0f,1.0f},
                {3.0f,-6.0f,3.0f,0.0f},
                {-3.0f,3.0f,0.0f,0.0f},
                {1.0f,0.0f,0.0f,0.0f}};

void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float* a) {
	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void parsePatchesFile(string fname,vector<vector<float> > * controlPoints,vector<int> * indexes){
    std::ifstream fp;
    fp.open(fname,ios::in);
    string line;

    int number_patches = 0;
    int number_controlPoints = 0;
    
    //read number of patches
    getline(fp,line); 
    number_patches = stoi(line);

    string token;
    int posFound = 0;

    //parse pacthes indexes
    for(int i=0;i<number_patches;i++){
        getline(fp,line);
       
       while((posFound = line.find(",")) != -1){
        token = line.substr(0,posFound);
        indexes->push_back(stoi(token));
        line.erase(0,posFound+1);
       }
       posFound = line.find("\n");
       token = line.substr(0,posFound);
       indexes->push_back(stoi(token));
    }

    if(number_patches*16 != indexes->size())
        cout << "Each patch needs to have 16 points!!";

    //read number of control points
    getline(fp,line);
    number_controlPoints = stoi(line);

    //parse control points
    for(int i=0;i<number_controlPoints;i++){
        getline(fp,line);
        int j = 0;
        vector<float> point;
        line.erase(0,1);
        while(j<2){  
            posFound = line.find(",");
            token = line.substr(0,posFound);
            line.erase(0,posFound+1);
            point.push_back(stof(token));
            j++;
        }
        posFound = line.find("\n");
        token = line.substr(0,posFound);
        line.erase(0,posFound+1);
        point.push_back(stof(token));
        controlPoints->push_back(point);
    }
    fp.close();
}

void compute_point(float u,float v,float **pX,float **pY,float **pZ,float * coords){
    //vector U
    float U[4] = { u*u*u, u*u, u, 1};
    //vector V
	float V[4] = { v*v*v, v*v, v, 1};

    //Point(u,v) = U * M * P(x,y,z) * M_t * V
    //M_t = M   
    float MV[4];
	multMatrixVector(*M,V,MV);

    float PMV[3][4];
	multMatrixVector((float *)pX,MV,PMV[0]);
	multMatrixVector((float *)pY,MV,PMV[1]);
	multMatrixVector((float *)pZ,MV,PMV[2]);

    float MPMV[3][4];
	multMatrixVector(*M,PMV[0],MPMV[0]);
	multMatrixVector(*M,PMV[1],MPMV[1]);
	multMatrixVector(*M,PMV[2],MPMV[2]);

    float UMPMV[3][4];
	multMatrixVector(U,MPMV[0],UMPMV[0]);
	multMatrixVector(U,MPMV[1],UMPMV[1]);
	multMatrixVector(U,MPMV[2],UMPMV[2]);
    
    for(int i = 0; i < 3; i++) {
		coords[i] = 0.0f;
		for(int j = 0; j < 4; j++) {
			coords[i] += U[j] * MPMV[i][j];
        }
    } 
}

void write_bezier(char * fname,int tessellation){
    vector<vector<float> > controlPoints;
    vector<int> indexes;
    parsePatchesFile(fname,&controlPoints,&indexes);
    cout << indexes.size() << "\n";
    cout << controlPoints.size() << "\n";
    /*
    for (int i : indexes)
        cout << i << " ";
    cout << "\n";
    for (auto v: controlPoints){
        for (auto i : v)
            cout << i << " ";

        cout << "\n";
    }*/

    //component X of P matrix
    float pX[4][4];
    //component Y of P matrix
    float pY[4][4];
    //component Z of P matrix
    float pZ[4][4];

    points ps =  points();
    //build patch by pacth
    for(int i=0;i<indexes.size()-1;){
        int p = i/16;
        cout << "patch:" << p << "\n";
        cout.flush();
        //save points for one patch 

        //estoura nesta ciclo na última patch!!!!
        for(int l=0;l<4;l++){
            for(int c=0;c<4;c++){
                pX[l][c] = controlPoints[indexes[i]][0];
                pY[l][c] = controlPoints[indexes[i]][1];
                pZ[l][c] = controlPoints[indexes[i]][2];
                i++;
            }
        }

        point grid[tessellation+1][tessellation+1];
        int point_count=0;
        for(int u=0;u<=tessellation;u++){
            float coords[3];
            float s1[3];
            float s2[3];

            for(int v=0;v<=tessellation;v++){
                compute_point(u/tessellation,v/tessellation,(float **)pX, (float **)pY, (float **) pZ,coords);
                grid[u][v] = point(coords[0],coords[1],coords[2]);
                cout << "coords:";
                cout << "(" << coords[0] << ";";
                cout << coords[1] << ";";
                cout << coords[2] << ")";
                cout << "\n";
                cout.flush();
            }   
        }

        //triangulation
        for(int u=0;u<tessellation;u++){
            for(int v=0;v<=tessellation;v++){
                
                ps.add_point(grid[u][v]);
                ps.add_point(grid[u+1][v]);
                ps.add_point(grid[u+1][v+1]);
               
                ps.add_point(grid[u+1][v+1]);
                ps.add_point(grid[u][v+1]);
                ps.add_point(grid[u][v]);
                
            }
        }
    }
    FILE * fp = fopen("bezier.3d","w+");
    write_points(ps,fp);
    fclose(fp);
}

/*
TODO:
-> possivel bug no calculo de pontos
-> o calculo das derivadas é só para usar na iluminação
*/


