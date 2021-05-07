#include "Asset.h"
#include "pgr.h"

namespace vpr {

class ShaderAsset : public Asset {
    public:
    bool loadFromPath(const std::string &path) override;
    void use();


    private:

    GLuint handle;
}

}