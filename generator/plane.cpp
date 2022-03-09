#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <list>
#include "plane.h"
#include "../Utilities/point.cpp"
#include <iostream>

int write_plane(float size, int div, char* fname) {
    if (size > 0 && div > 0) {
        std::map<size_t,point> pointsHash;
        list<size_t> indexList;

        FILE* file = fopen(fname, "w+");
        float x, z;

        x = -size / 2;
        z = size / 2;

        float initz = z;
        float part = size / div;

        int i1 = 0;

        while (i1 < div) {
            int i2 = 0;
            while (i2 < div) {
                float ax = x + part;
                float az = z - part;
                
                point p1 = point(x, 0, az);
                pointsHash.insert(std::make_pair(p1.get_hash_code(), p1));
                indexList.push_back(p1.get_hash_code());

                point p2 = point(x, 0, z);
                pointsHash.insert(std::make_pair(p2.get_hash_code(), p2));
                indexList.push_back(p2.get_hash_code());

                point p3 = point(ax, 0, z);
                pointsHash.insert(std::make_pair(p3.get_hash_code(), p3));
                indexList.push_back(p3.get_hash_code());


                point p4 = point(ax, 0, z);
                pointsHash.insert(std::make_pair(p4.get_hash_code(), p4));
                indexList.push_back(p4.get_hash_code());

                point p5 = point(ax, 0, az);
                pointsHash.insert(std::make_pair(p5.get_hash_code(), p5));
                indexList.push_back(p5.get_hash_code());

                point p6 = point(x, 0, az);
                pointsHash.insert(std::make_pair(p6.get_hash_code(), p6));
                indexList.push_back(p6.get_hash_code());

                i2 = i2 + 1;
                z = az;
            }
            x = x + part;
            z = initz;
            i1 = i1 + 1;
        }
        fclose(file);
        /*
        for (auto & x : pointsHash)
        {
            std::cout << x.first  // string (key)
                << ':'
                << x.second.getX() // string's value 
                << std::endl;
        }

        for (auto& x : indexList)
        {
            std::cout << x
                << std::endl;
        }
        */
    }
    return 0;
}