#include "../../include/assets/ShaderAsset.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

namespace vpr {


// TODO: input validation
bool ShaderAsset::loadConfiguration(string path) {
     std::ifstream file(path.c_str(), std::ios::in);
    if(!file) return false;

    nlohmann::json shaderConfig;
    file >> shaderConfig;

    ShaderConfiguration &configuration = this->configuration;

    configuration.fragmentShader = shaderConfig["fragment"].get<string>();
    configuration.vertexShader = shaderConfig["vertex"].get<string>();

    for(auto attributesIt = shaderConfig["attributes"].begin();attributesIt != shaderConfig["attributes"].end(); ++attributesIt) {
        configuration.attributes.push_back(attributesIt.value().get<string>());
    }

    for(auto uniformsIt = shaderConfig["uniforms"].begin();uniformsIt != shaderConfig["uniforms"].end(); ++uniformsIt) {
        configuration.uniforms.push_back(uniformsIt.value().get<string>());
    }

    if(shaderConfig["uniformBufferObject"].is_array()) {
        for(auto uniformsBufferObjectIt = shaderConfig["uniformBufferObject"].begin();uniformsBufferObjectIt != shaderConfig["uniformBufferObject"].end(); ++uniformsBufferObjectIt) {
            configuration.uniformBufferObjects.push_back(uniformsBufferObjectIt.value().get<string>());
        }
    }


    return true;
}

ShaderConfiguration* ShaderAsset::getConfiguration() {
    return &configuration;
}

bool ShaderAsset::load(string path) {
    loadConfiguration(path);


    fs::path p = path;
    p = p.remove_filename();
    this->fragmentShaderPath = p.append(this->configuration.fragmentShader).string();
    p.remove_filename(); // cuz this shit is not immutable
    this->vertexShaderPath = p.append(this->configuration.vertexShader).string();

    std::cout << "paths" << this->fragmentShaderPath << " " << this->vertexShaderPath << std::endl;
    

    GLuint fragmentShader, vertexShader;
    bool resFrag = this->loadShader(this->fragmentShaderPath, GL_FRAGMENT_SHADER, fragmentShader);
    bool resVert = this->loadShader(this->vertexShaderPath, GL_VERTEX_SHADER, vertexShader);

    if(!resFrag || !resVert) return false;

    this->program = glCreateProgram();

    glAttachShader(this->program, fragmentShader);
    glAttachShader(this->program, vertexShader);

    setAttributeLocations();
    // setUniformLocations();

    glLinkProgram(this->program);

    int linkStatus;
    char infoLog[512];
    glGetProgramiv(this->program, GL_LINK_STATUS, &linkStatus);
    if(!linkStatus) {
        glGetShaderInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "Shader linking error\n" << infoLog;
        return false;
    }
    
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    return true;
}

void ShaderAsset::bindUniformBufferObjectLocations() {
    for(auto uniformBufferObjectName: configuration.uniformBufferObjects) {
        UniformBufferObjectDescription description = fixedUniformBufferLocations[uniformBufferObjectName];
        GLuint uniformBlockLocation = glGetUniformBlockIndex(program, description.shaderVariableName.c_str());
        glUniformBlockBinding(program, uniformBlockLocation, description.location);
        CHECK_GL_ERROR();

    }
}

bool ShaderAsset::loadShader(const string& shaderPath, GLenum shaderType, GLuint &shader) {

    string code;
    std::ifstream shaderFile;

    std::cout << "Loading shader file " << shaderPath << std::endl;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(shaderPath);
        if(!shaderFile) {
            std::cout << "Could not open file " << shaderPath << std::endl;
            return false;
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        code = shaderStream.str();

    } catch(std::ifstream::failure e) {
        shaderFile.close();
        std::cout << "Could not read from shader file " << shaderPath << std::endl;
        return false;
    }

    const char* shaderCode = code.c_str();
    int success;
    char infoLog[512];

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);


    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader "<< shaderPath <<" compilation error\n" << infoLog;
        return false;
    }

    return true;    
}

void ShaderAsset::setAttributeLocations() {
    for(string& attribute: this->configuration.attributes) {
        GLuint& location = fixedAttributeLocations[attribute].location;
        
        glBindAttribLocation(this->program, location, attribute.c_str());
    }
}

void ShaderAsset::setUniformLocations() {
    for(string& uniform: this->configuration.uniforms) {
        GLuint& location = fixedUniformLocations[uniform].location;
        std::cout << "binding " << uniform << " to " << location << std::endl;
        glBindAttribLocation(this->program, location, uniform.c_str());
        CHECK_GL_ERROR();
    }
}

void ShaderAsset::use() {
    glUseProgram(program);
}

}