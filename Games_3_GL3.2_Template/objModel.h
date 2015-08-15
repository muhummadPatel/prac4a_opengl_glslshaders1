#ifndef OBJMODEL_H
#define OBJMODEL_H


#include <string>
#include <vector>

#include "glm/glm.hpp"

//class to load an obj model file.
//Adapted, as allowed under the WTFPL license used, from the tutorial at:
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

class objModel
{
    public:
        //std::veectors to store the vertex atrributes
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;

        objModel();
        ~objModel();
        bool read(const char *filename);
};

#endif // OBJMODEL_H
