#pragma once
#include <vector>
#include <stdio.h>

#include "pgr.h"

#include "../Types.h"

namespace vpr {

#pragma pack(push, 1)
#define SUN_LIGHT_DATA_SIZE_PADDED 48
struct SunLightData {
    glm::vec4 color;
    glm::vec4 angle;
    float strength{0};

    float padding[3];
}; 

#define POINT_LIGHT_DATA_SIZE_PADDED 64
struct PointLightData {
    glm::vec4 position;
    glm::vec4 color;
    glm::vec4 attentuation;
    float strength{0};

    float padding[3];
};

#define SPOT_LIGHT_DATA_SIZE_PADDED 80
struct SpotLightData {
    glm::vec4 color;
    glm::vec4 position;
    glm::vec4 angle;
    glm::vec4 cone;
    float strength{0};
    
    float padding[3];
    
};

struct LightsData {
    SunLightData sun_lights[MAX_SUN_LIGHTS];
    PointLightData point_lights[MAX_POINT_LIGHTS];
    SpotLightData spot_lights[MAX_SPOT_LIGHTS];
    
    int num_sun_lights;
    int num_point_lights;
    int num_spot_lights;
};

#pragma pack(pop)


class LightsUBO {
    public: 
    LightsUBO();

    bool uploadData(std::vector<SunLightData*>&, std::vector<PointLightData*>&, std::vector<SpotLightData*>&);
    size_t getSize();

    void bind();
    void unbind();

    private:

    LightsData lightsData;
    GLuint handle;

};

}