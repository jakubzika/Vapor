#include <iostream>

#include "../../include/gl/LightsUBO.h"

namespace vpr {

/* 

----------------

struct SunLight {  base alignment        aligned offset
     vec4 color;          16                   0 
     vec4 angle;          16                  16
     float strength;       4                  20
 };

total size: 24
padded size: 32

----------------

struct PointLight {  base alignment      aligned offset
    vec4 position;       16                   0
    vec4 color;          16                  16
    vec4 attentuation;   16                  32
    float strength;       4                  36
};

total size: 40
padded size: 48
----------------

 struct SpotLight {   base alignment      aligned offset
     vec4 color;          16                   0
     vec4 position;       16                  16
     vec4 angle;          16                  32
     vec4 cone;           16                  48
     float strength;       4                  52  
 };

 total size: 56
padded size: 64
----------------
 

layout (std140) uniform lights {               base aligmnent      alligned offset
    int num_sun_lights;                            4                        0
    int num_point_lights;                          4                        4
    int num_spot_lights;                           4                        8
    // 8 padding
    SunLight sun_lights[MAX_SUN_LIGHTS];          24 * MAX_SUN_LIGHTS      16
    PointLight point_lights[MAX_POINT_LIGHTS];    40 * MAX_POINT_LIGHTS    16 + (32 * MAX_SUN_LIGHTS)
    SpotLight spot_lights[MAX_SPOT_LIGHTS];       56 *MAX_SPOT_LIGHTS      16 + (32 * MAX_SUN_LIGHTS) + (56 * MAX_POINT_LIGHTS) 
};y

total size = 16 + (32 * MAX_SUN_LIGHTS) + (48 * MAX_POINT_LIGHTS) + (64 * MAX_SPOT_LIGHTS)

*/

LightsUBO::LightsUBO() {
    glGenBuffers(1, &handle);
    glBindBuffer(GL_UNIFORM_BUFFER,handle);
    glBufferData(GL_UNIFORM_BUFFER, getSize(),NULL, GL_STATIC_DRAW);

    unbind();

    glBindBufferRange(GL_UNIFORM_BUFFER, LightsUniformBufferObject.location, handle, 0, getSize());

}

size_t LightsUBO::getSize() {
    // return 12 + (32 * MAX_SUN_LIGHTS) + (48 * MAX_POINT_LIGHTS) + (64 * MAX_SPOT_LIGHTS);
    return sizeof(LightsData);
}

bool LightsUBO::uploadData(std::vector<SunLightData*> &sunLightData, std::vector<PointLightData*> &pointLightData, std::vector<SpotLightData*> &spotLightData) {
    bind();

    lightsData.num_sun_lights = sunLightData.size();
    lightsData.num_point_lights = pointLightData.size();
    lightsData.num_spot_lights = spotLightData.size();

    for(int i = 0; i < sunLightData.size(); i++) {
        memcpy(&lightsData.sun_lights[i], sunLightData[i], sizeof(SunLightData));
    }

    for(int i = 0; i < pointLightData.size(); i++) {
        memcpy(&lightsData.point_lights[i], pointLightData[i], sizeof(PointLightData));
    }

    for(int i = 0; i < spotLightData.size(); i++) {
        memcpy(&lightsData.spot_lights[i], spotLightData[i], sizeof(SpotLightData));
    }

    glBufferSubData(GL_UNIFORM_BUFFER,0, getSize(), &lightsData);
    CHECK_GL_ERROR();
    

    unbind();

    return true;
}

void LightsUBO::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER, handle);
}

void LightsUBO::unbind() {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


}