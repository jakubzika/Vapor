#pragma once
#include "Asset.h"
#include "pgr.h"

#include <vector>

namespace vpr {

struct ShaderConfiguration {
    string fragmentShader;
    string vertexShader;

    std::vector<string> uniformBufferObjects;
    std::vector<string> attributes;
    std::vector<string> uniforms;
};

class ShaderAsset : public Asset {
    public:
    bool load(string) override;
    void use();
    ShaderConfiguration* getConfiguration();
    GLuint getProgram() {return program;};

    private:
    
    bool loadShader(const string &path, GLenum shaderType, GLuint &shader); 


    bool loadConfiguration(string);
    ShaderConfiguration configuration;


    void setUniformLocations();
    void setAttributeLocations();
    void bindUniformBufferObjectLocations();

    string fragmentShaderPath;
    string vertexShaderPath;

    GLuint program;
};

}