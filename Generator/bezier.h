#ifndef BEZIER_H
#define BEZIER_H
//#include "writer.h"

int write_bezier();
void parsePatchesFile(string fname,vector<vector<float> > * controlPoints,vector<int> * indexes);
#endif