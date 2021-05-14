#include "../../include/scene/LightEntity.h"

namespace vpr {

LightEntity::LightEntity() {
    this->type = LIGHT_POINT;
}

LightEntity::LightEntity(LightType type) {
    this->type = type;
}

void LightEntity::generateRenderingData(SceneRenderingInstance& renderer) {
    // auto* sunData = &data.sun;
    // auto* pointData = &data.point;
    // auto* spotData = &data.spot;

    switch(type) {
        case LIGHT_SUN:
        std::cout << "Adding sunlight\n";
        renderer.addSunLight(&sunLightData);
        
        break;
        case LIGHT_POINT:
        renderer.addPointLight(&pointLightData);
        break;
        case LIGHT_SPOT:
        renderer.addSpotLight(&spotLightData);
        break;
    }
}

void LightEntity::updatePositions(glm::mat4 model, glm::mat3 modelNormals) {
switch(type) {
        case LIGHT_SUN:
            sunLightData.angle = glm::vec4(rotation,0.0f);
            sunLightData.color = glm::vec4(color,0.0f);
            sunLightData.strength = strength;
        break;
        case LIGHT_POINT:
            pointLightData.attentuation = glm::vec4(attentuation,0.0f);
            pointLightData.color = glm::vec4(color,0.0);
            pointLightData.position = glm::vec4(position,0.0);
            pointLightData.strength = strength;
        break;
        case LIGHT_SPOT:
            spotLightData.angle = glm::vec4(rotation,0.0f);
            spotLightData.color = glm::vec4(color, 0.0f);
            spotLightData.cone = glm::vec4(cone,0.0f);
            spotLightData.position = glm::vec4(position,0.0f);
            spotLightData.strength = strength;
        break;
    }
}


void LightEntity::setAttentuation(float constant, float linear, float quadratic) {
    setAttentuation(glm::vec3(constant, linear, quadratic));
}

void LightEntity::setAttentuation(glm::vec3 attentuation) {
    this->attentuation = attentuation;
}

void LightEntity::setCone(float cutoff) {
    this->cone = glm::vec3(cutoff,0.0,0.0);
}

void LightEntity::setColor(float r,float g,float b) {
    setColor(glm::vec3(r,g,b));
}
void LightEntity::setColor(glm::vec3 color) {
    this->color = color;
}

void LightEntity::setStrength(float srength) {
    this->strength = strength;
}

}