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

    //read number of control points
    getline(fp,line);
    number_controlPoints = stoi(line);

    //parse control points
    for(int i=0;i<number_controlPoints-1;i++){
        getline(fp,line);
        int j = 0;
        vector<float> point;
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

void write_bezier(char * fname,int tessellation){





}