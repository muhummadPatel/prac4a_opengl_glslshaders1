/*
 * Implementation of stlModel class.
 *
 * Muhummad Yunus Patel     27-April-2015
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "stlModel.h"

using namespace std;

//destructor to clean up the points array
stlModel::~stlModel(){
    if(points != NULL){
        delete[] points;
    }

    if(normals != NULL){
        delete[] normals;
    }
}

//function to read in binary stl file with the given filename
bool stlModel::read(string filename){
    if(filename == "TEST"){
        float testTri[] = { -0.5f, -0.5f, 0.0f, 1.0f,
                            0.5f, -0.5f, 0.0f, 1.0f,
                            0.0f,  0.5f, 0.0f, 1.0f };

        numTriangles = 1;
        points = new float[numTriangles * 12];
        for(int i  = 0; i < 12; i++){
            points[i] = testTri[i];
        }

        float testCols[] = {
          1.0f, 0.0f,  0.0f,
          0.0f, 1.0f,  0.0f,
          0.0f, 0.0f,  1.0f
        };
        colours = new float[numTriangles * 3 * 3];
        for(int i  = 0; i < 9; i++){
            colours[i] = testCols[i];
        }

        return true;
    }

    ifstream infile(filename.c_str(), ios::in|ios::binary);

    if(!infile){
        cout << "DIDNT OPEN FILE" << endl;
        return false;
    }

    //read in the header
    char buffer[80];
    infile.read(buffer, 80);

    //read in the number of triangles
    char buffer2[4];
    infile.read(buffer2, 4);
    numTriangles = *((unsigned int*) buffer2);

    cout << "number of triangles: " << numTriangles << endl;

    //read in the triangles
    points = new float[numTriangles * 3 * 4];
    normals = new float[numTriangles * 3 * 3]; //normal for every vertex is same as for the face
    int c = 0;
    int d = 0;
    //ostringstream oss;
    for(int i = 0; i < numTriangles; i++){
        //read in the normal vector
        char normalBuff[12];
        infile.read(normalBuff, 12);
        float* norm = (float*) normalBuff;

        //read each vertex of the triangle and add coords to points array
        for(int i = 0; i < 3; i++){
            char vert1Buff[12];
            infile.read(vert1Buff, 12);
            float* v1 = (float*) vert1Buff;

            points[c] = v1[0];   //x
            points[c+1] = v1[1]; //y
            points[c+2] = v1[2]; //z
            points[c+3] = 1.0f;  //w

            normals[d] = norm[0];   //x
            normals[d+1] = norm[1]; //y
            normals[d+2] = norm[2]; //z
            //oss << normals[c] << " " << normals[c+1] << " " << normals[c+2] << " " << normals[c+3] << endl;
            c+=4;
            d+=3;
        }

        //read and discard the 2 byte attribute
        char attrib[2];
        infile.read(attrib, 2);
    }

    int colLen = numTriangles * 3 * 3;
    colours = new float[colLen];
    for(int i  = 0; i < colLen; i+=3){
//        if(i < colLen/3){
            colours[i] = 0.0f;
            colours[i+1] = 0.0f;
            colours[i+2] = 1.0f;
//        }else if(i < (2 * (colLen/3))){
//            colours[i] = 0.0f;
//            colours[i+1] = 1.0f;
//            colours[i+2] = 0.0f;
//        }else{
//            colours[i] = 1.0f;
//            colours[i+1] = 0.0f;
//            colours[i+2] = 0.0f;
//        }
    }

    //cout << "normals ___" << endl;
    //cout << oss.str() << endl;
    infile.close();
    return true;
}
