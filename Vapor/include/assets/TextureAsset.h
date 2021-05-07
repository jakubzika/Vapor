#include "Asset.h"

#include "pgr.h"

namespace vpr {

class TextureAsset: public Asset {

    public:
    bool loadFromPath(const std::string& path);

    private:

    GLuint handle;
    GLenum textureType;
};

}