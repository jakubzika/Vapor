#include "../../include/assets/TextureAsset.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb/stb_image.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

namespace vpr {

bool TextureAsset::loadConfiguration(string path) {
    std::ifstream file(path.c_str(), std::ios::in);
    if(!file) return false;

    nlohmann::json textureConfig;
    file >> textureConfig;

    TextureConfiguration& configuration = this->configuration;

    configuration.kind = textureConfig["kind"].get<string>();
    configuration.texture = textureConfig["texture"].get<string>();
    configuration.type = textureConfig["type"].get<string>();

    return true;
}

bool TextureAsset::load(string path) {
    loadConfiguration(path);

    if(configuration.kind == "2D") kind = GL_TEXTURE_2D;
    else if(configuration.kind == "3D") kind = GL_TEXTURE_3D;
    else if(configuration.kind == "CUBE_MAP")kind = GL_TEXTURE_CUBE_MAP;
    type = textureTypeToMask[configuration.type];

    if(configuration.kind == "2D") {
        fs::path texturePath = path;
        texturePath = texturePath.remove_filename();
        texturePath = texturePath.append(configuration.texture);
        load2DTexture(texturePath);
    }
    else if(configuration.kind == "CUBE_MAP") {
        fs::path basePath = path;
        fs::path fileExtension = fs::path(configuration.texture).extension();
        fs::path fileStem = fs::path(configuration.texture).stem();
        fs::path directory = basePath.remove_filename();

        fs::path texturePath[6];
        for(int i = 0; i < 6; i++) {
            std::stringstream paddedIdx;
            paddedIdx << std::setw(4) << std::setfill('0') << i+1;
            texturePath[i] = directory / (fileStem.string() + "_" + paddedIdx.str() + fileExtension.string());
        }
        loadCubemapTexture(texturePath);

    }

    return true;
}

bool TextureAsset::load2DTexture(fs::path texturePath) {
    int width,height, channels;

    try {
        stbi_set_flip_vertically_on_load(true);
        unsigned char* imageData = stbi_load(texturePath.string().c_str(),&width,&height,&channels, 0);
        CHECK_GL_ERROR();

        glGenTextures(1,&handle);
        glBindTexture(kind, handle);
        CHECK_GL_ERROR();

        std::cout << "Loading texture " << texturePath;
        std::cout<< " width: " << width << " height: " << height;
        std::cout << " handle: " << handle << std::endl;
        
        glTexParameteri(kind, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(kind, GL_TEXTURE_WRAP_T, GL_REPEAT);  
        CHECK_GL_ERROR();


        
        glTexParameteri(kind, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(kind, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        CHECK_GL_ERROR();

        
        if(kind == GL_TEXTURE_2D) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            CHECK_GL_ERROR();
        }

        glGenerateMipmap(kind);
        CHECK_GL_ERROR();
        return true;
    } catch(...) {
        std::cout << "Could not load texture asset: "<< path << std::endl;
        return false;
    }
}

bool TextureAsset::loadCubemapTexture(fs::path texturePaths[6]) {
    int width, height, nrChannels;
    unsigned char* data;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

    for(int i = 0; i < 6; i++) {
        std::cout << "Loading cubemap texture " << texturePaths[i].string() << std::endl;
        stbi_set_flip_vertically_on_load(false);
        data = stbi_load(texturePaths[i].string().c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  

    return true;
}

void TextureAsset::use() {
    // std::cout << "use texture " << configuration.texture << std::endl;
    glActiveTexture(textureMaskToUnits[type]);
    glBindTexture(kind,handle);
}



}