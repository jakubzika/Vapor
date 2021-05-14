#include "../../include/assets/MeshAsset.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

#include "../../include/nlohmann/json.hpp"
#include "../../include/Util.h"
#include "../../include/gl/VecHash.h"

namespace vpr {

bool MeshAsset::loadConfiguration(const std::string &path) {

    std::ifstream file(path.c_str(), std::ios::in);
    if(!file) {
        std::cout << "Could not open mesh configuration file " << path << std::endl;   
        return false;
    }

    nlohmann::json meshConfig;
    file >> meshConfig;

    MeshConfiguration &configuration = this->configuration;
    configuration.type = getModelType(meshConfig["type"].get<std::string>());
    //configuration.material = meshConfig["material"].get<std::string>();
    configuration.mesh = meshConfig["mesh"].get<std::string>();
    configuration.name = meshConfig["name"].get<std::string>();

    for(auto attributesIt = meshConfig["attributes"].begin(); attributesIt != meshConfig["attributes"].end(); ++attributesIt) {
        configuration.attributes.push_back(attributesIt.value().get<std::string>());
    }

    file.close();

    return true;
}

// bool MeshAsset::loadFromConfiguration(json configuration) {
//     return false;
// }

bool MeshAsset::load(string configurationPath) {

    this->path = configurationPath;
    this->loadConfiguration(configurationPath);

    std::filesystem::path p = configurationPath;
    p = p.remove_filename();

    std::filesystem::path objPath = p.append(this->configuration.mesh);
    

    std::cout << "opening file " << objPath.string() << std::endl;
    std::ifstream file(objPath.c_str(), std::ios::in);

    std::vector<glm::vec3> vertexList;
    std::vector<glm::vec2> texturesList;
    std::vector<glm::vec3> normalsList;

    std::vector<VertexTriangle> trianglesList;

    if(!file) return false;
    std::string buffer;

    int faceIdx = 0;

    while(!file.eof()) {
        file >> buffer;

        // parses vertices
        if(buffer == "v") {
            vertexList.push_back({});
            file >> vertexList.back().x >> vertexList.back().y >> vertexList.back().z;
        }
        // parses normals
        else if(buffer == "vn") {
            normalsList.push_back({});
            file >> normalsList.back().x >> normalsList.back().y >> normalsList.back().z;
        }
        // parses uv's
        else if(buffer == "vt") {
            texturesList.push_back({});
            file >> texturesList.back().x >> texturesList.back().y;
        }
        // parses faces and indexes for vertices,normals,uvs
        else if(buffer == "f") {
            // we expect triangulated mesh so each face that has more than 3 verticies is a crash
            std::vector<glm::vec3> indices;
            std::string line;
            std::getline(file, line);

            if(line == "") continue;

            std::istringstream iss(line);
            std::string word;
            char c;

            for(int i = 0; i < 3; i++) {

                iss >> word;
                std::istringstream vals(word);

                indices.push_back({});

                vals >> indices.back().x;
                vals >> c;
                vals >> indices.back().y;
                vals >> c;
                vals >> indices.back().z;
                
            }
            
            trianglesList.push_back({
                {indices[0].x,indices[0].y,indices[0].z},
                {indices[1].x,indices[1].y,indices[1].z},
                {indices[2].x,indices[2].y,indices[2].z},
                });   

            faceIdx++;

        }

    }

    this->constructBuffers(vertexList, texturesList, normalsList,trianglesList);
    this->constructVAO();

    return true;
}

// uglyy

void MeshAsset::bindFromName(std::string name) {
    if(name == "position")
        (*this->verticesBuffer).bind();
    else if(name == "normal")
        (*this->normalsBuffer).bind();
    else if(name == "uv")
        (*this->uvsBuffer).bind();

}


void MeshAsset::constructVAO() {
    if(this->VAO != 0) glDeleteVertexArrays(1,&this->VAO);
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO); 

        CHECK_GL_ERROR();


    for(auto& attributeName: this->configuration.attributes) {

        std::cout << "binding " << attributeName << std::endl;
        this->bindFromName(attributeName);

        ShaderAttributeDescription attribute = fixedAttributeLocations[attributeName];
        glEnableVertexAttribArray(attribute.location);
        glVertexAttribPointer(attribute.location,attribute.count,attribute.type,GL_FALSE,attribute.size, (void*)0);

        CHECK_GL_ERROR();
    }

    this->indicesBuffer->bind();

    glBindVertexArray(0);
}

void MeshAsset::constructBuffers(std::vector<glm::vec3> &vertices,std::vector<glm::vec2> &uvs,std::vector<glm::vec3> &normals,std::vector<VertexTriangle> &triangles) {
    std::unordered_map<glm::tvec3<unsigned int>, uint32_t,KeyFuncs, KeyFuncs> uniqueVertices{};

    std::vector<uint32_t> indices;
    std::vector<GLfloat> verticesReordered;
    std::vector<GLfloat> normalsReordered;
    std::vector<GLfloat> uvsReordered;

    int bufferEndIndex = 0;


    int face = 0;

    for(const auto& triangle : triangles) {
        
        // std::cout<<"face " << face++ << std::endl;

        glm::tvec3<unsigned int> faceVertices[] = {triangle.v1,triangle.v2,triangle.v3};



        for(const auto& faceVertex: faceVertices ) {
                        
            // std::cout << "face vertex " << faceVertex.x << " " << faceVertex.y << " " << faceVertex.z << std::endl;
                
            if(uniqueVertices.count(faceVertex) == 0) {
                auto& v = vertices[faceVertex.x-1];
                verticesReordered.push_back(v.x);
                verticesReordered.push_back(v.y);
                verticesReordered.push_back(v.z);

                auto& vt = normals[faceVertex.z-1];
                normalsReordered.push_back(vt.x);
                normalsReordered.push_back(vt.y);
                normalsReordered.push_back(vt.z);

                auto& vn = uvs[faceVertex.y-1];
                uvsReordered.push_back(vn.x);
                uvsReordered.push_back(vn.y);
                

                indices.push_back(bufferEndIndex++);

                uniqueVertices[faceVertex] = bufferEndIndex;



            } else {
                // auto it = uniqueVertices.find(faceVertex);
                uint32_t vertexIndex = uniqueVertices[faceVertex]-1;


                indices.push_back(vertexIndex);

            }
        }
    }

    if(this->verticesBuffer) delete this->verticesBuffer;
    if(this->uvsBuffer) delete this->uvsBuffer;
    if(this->normalsBuffer) delete this->normalsBuffer;
    if(this->indicesBuffer) delete this->indicesBuffer;

    this->verticesBuffer = new GLBuffer<GLfloat>(verticesReordered,3*sizeof(GLfloat),GL_ARRAY_BUFFER);
    this->uvsBuffer = new GLBuffer<GLfloat>(uvsReordered, 2*sizeof(GLfloat),GL_ARRAY_BUFFER);
    this->normalsBuffer = new GLBuffer<GLfloat>(normalsReordered, 3*sizeof(GLfloat),GL_ARRAY_BUFFER);
    this->indicesBuffer = new GLBuffer<GLuint>(indices, 3*sizeof(GLuint), GL_ELEMENT_ARRAY_BUFFER);

    this->numVertices = indices.size();
}

void MeshAsset::use() {
    glBindVertexArray(this->VAO);
}

}