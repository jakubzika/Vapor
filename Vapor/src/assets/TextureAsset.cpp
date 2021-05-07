#include "../../include/assets/TextureAsset.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb/stb_image.h"

#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

namespace vpr {

bool TextureAsset::loadFromPath(const std::string& path) {
    int width,height, channels;
    try {

        unsigned char* imageData = stbi_load(path.c_str(),&width,&height,&channels, 0);

        GLuint textureHandle;
        glGenTextures(1,&textureHandle);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);  

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        return true;
    } catch(...) {
        std::cout << "Could not load texture asset: "<< path << std::endl;
        return false;
    }
}



}