#pragma once

#include "pgr.h"

#include "../gl/LightsUBO.h"
#include "../renderer/SceneRenderingInstance.h"
#include "../Types.h"


#include "SceneObject.h"
#include "SceneEntity.h"

namespace vpr {

enum LightType {
    LIGHT_SUN,LIGHT_POINT,LIGHT_SPOT
};

struct SunLightData;
struct PointLightData;
struct SpotLightData;

class SceneObject;
class SceneEntity;
class SceneRenderingInstance;

class LightEntity : public SceneEntity {
    public:
    LightEntity();
    LightEntity(LightType type);

    void generateRenderingData(SceneRenderingInstance& renderer);
    void updatePositions(glm::mat4 model, glm::mat3 modelNormals, bool hidden);

    void setAttentuation(float, float, float);
    void setAttentuation(glm::vec3);

    void setCone(float,float);

    void setColor(float,float,float);
    void setColor(glm::vec3);

    void setStrength(float);

    private:
    LightType type;

    glm::vec3 attentuation;
    glm::vec3 cone;
    glm::vec3 color;
    float strength;

    SunLightData sunLightData;
    PointLightData pointLightData;
    SpotLightData spotLightData;

};

}