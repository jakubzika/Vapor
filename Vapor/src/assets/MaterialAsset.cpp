#include "../../include/assets/MaterialAsset.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

#include "../../include/nlohmann/json.hpp"
#include "../../include/Util.h"

namespace vpr {


bool MaterialAsset::loadConfiguration(const std::string &path) {
    this->path = path;

    std::ifstream file(path.c_str(), std::ios::in);
    if(!file) return false;

    nlohmann::json materialConfig;
    file >> materialConfig;

    MaterialConfiguration &configuration = this->configuration;
    configuration.type = getModelType(materialConfig["type"].get<std::string>());
    configuration.fragmentShader = materialConfig["fragment-shader"].get<std::string>();
    configuration.vertexShader = materialConfig["vertex-shader"].get<std::string>();
    configuration.name = materialConfig["name"].get<std::string>();

    // TODO: load configuration uniforms


    for(auto attributesIt = materialConfig["attributes"].begin();attributesIt != materialConfig["attributes"].end(); ++attributesIt) {
        configuration.attributes.push_back(attributesIt.value().get<std::string>());
    }

    for(auto uniformsIt = materialConfig["uniforms"].begin();uniformsIt != materialConfig["uniforms"].end(); ++uniformsIt) {
        configuration.uniforms.push_back(uniformsIt.value().get<std::string>());
    }



    file.close();

    return true;
}

bool MaterialAsset::loadFromPath(const std::string &configurationPath) {
    
    this->loadConfiguration(configurationPath);

    std::filesystem::path p = configurationPath;
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
    setUniformLocations();

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

bool MaterialAsset::loadShader(const std::string& shaderPath, GLenum shaderType, GLuint &shader) {

    std::string code;
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

void MaterialAsset::use() {
    glUseProgram(this->program);
}


void MaterialAsset::setAttributeLocations() {
    for(std::string& attribute: this->configuration.attributes) {
        GLuint& location = fixedAttributeLocations[attribute].location;
        
        glBindAttribLocation(this->program, location, attribute.c_str());
    }
}

void MaterialAsset::setUniformLocations() {
    for(std::string& uniform: this->configuration.uniforms) {
        GLuint& location = fixedUniformLocations[uniform].location;
        std::cout << "binding " << uniform << " to " << location << std::endl;
        glBindAttribLocation(this->program, location, uniform.c_str());
        CHECK_GL_ERROR();
    }
}

MaterialConfiguration MaterialAsset::getMaterialConfiguration() {
    return this->configuration;
}


}