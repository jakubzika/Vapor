#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "pgr.h"
#include "../Types.h"
#include "Asset.h"
#include "../gl/GLBUffer.h"
#include "../nlohmann/json.hpp"

namespace vpr {

struct VertexTriangle
{
    glm::tvec3<unsigned int> v1;
    glm::tvec3<unsigned int> v2;
    glm::tvec3<unsigned int> v3;
};

struct MeshConfiguration {
  std::string name;
  std::string mesh;
  ModelType type;
  std::string material;

  std::vector<std::string> attributes;
};

class MeshAsset: public Asset {

  public:
    bool loadFromPath(const std::string &path) override;
    // bool loadFromBuffer(void * data,std::size_t dataSize);

    ModelType modelType;

    GLuint getVerticiesVBO();
    GLuint getTextureVBO();
    GLuint getVerticiesIndicesEBO();

    void constructBuffers(std::vector<glm::vec3>&,std::vector<glm::vec2>&,std::vector<glm::vec3>&,std::vector<VertexTriangle>&);
    void constructVAO();

    bool loadConfiguration(const std::string&);

    // ugly ugly hack
    void bindFromName(std::string);

    void use();
    unsigned int numVertices;
    
  private:

    MeshConfiguration configuration;
    GLuint VAO = 0;

    // map of used buffers for solving the dynamic everything question
    GLBuffer<GLfloat> * verticesBuffer;
    GLBuffer<GLfloat> * uvsBuffer;
    GLBuffer<GLfloat> * normalsBuffer;
    GLBuffer<GLuint> * indicesBuffer;

};

}
