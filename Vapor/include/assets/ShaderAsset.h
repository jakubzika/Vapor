/**
 * \file       ShaderAsset.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Shader asset
 *
*/

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


    /**
     * @brief Binds uniforms to positions defined , alhough its not needed i think :)
     * 
     */
    void setUniformLocations();

    /**
     * @brief Binds attributes to predefined locations from Types.h
     * 
     */
    void setAttributeLocations();

    /**
     * @brief Binds Uniform buffer object to predefined locations
     * 
     */
    void bindUniformBufferObjectLocations();

    string fragmentShaderPath;
    string vertexShaderPath;

    GLuint program;
};

}