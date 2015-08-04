#ifndef STLMODEL_H
#define STLMODEL_H

#include <string>

class stlModel{
    public:
        unsigned long numTriangles;
        float* points;
        float* normals;
        float* colours; //TODO: remove. ONLY FOR TESTING
        stlModel(): numTriangles(0), points(NULL), normals(NULL){}
        ~stlModel();
        bool read(std::string filename);
};

#endif // STLMODEL_H
