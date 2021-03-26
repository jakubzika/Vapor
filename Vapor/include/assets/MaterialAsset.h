#pragma once

#include "pgr.h"
#include <vector>

#include "Asset.h"
#include "../Types.h"

namespace vpr {


struct MaterialConfiguration {
    std::string name;
    ModelType type;
    std::string fragmentShader,vertexShader;
    
    std::vector<std::string> uniforms;
    std::vector<std::string> attributes;
};

class MaterialAsset : public Asset {

    public:
    
    bool loadFromPath(const std::string &path) override;
    void use();

    MaterialConfiguration getMaterialConfiguration();
    
    private:

    GLuint program;
    ModelType modelType;

    std::string fragmentShaderPath;
    std::string vertexShaderPath;

    MaterialConfiguration configuration;

    bool loadShader(const std::string &path, GLenum shaderType, GLuint &shader); 
    bool loadConfiguration(const std::string &path);

    void setUniformLocations();
    void setAttributeLocations();

    // void
    // void createProgram(GLuint, GLuint);
};

}