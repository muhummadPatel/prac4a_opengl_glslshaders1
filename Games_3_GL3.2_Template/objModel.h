#ifndef OBJMODEL_H
#define OBJMODEL_H


#include <string>
#include <vector>

#include "glm/glm.hpp"

class objModel
{
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;

        objModel();
        ~objModel();
        bool read(char* filename);
};

#endif // OBJMODEL_H
