#include "../include/Util.h"

namespace vpr {

ModelType getModelType(std::string type) {
    if(type == "SOLID") return SOLID;
    else if(type =="TEXTURED") return TEXTURED;
    
    return UNKNOWN;
}

void sortByDistanceFromPoint(std::vector<std::tuple<MeshAsset*, MaterialAsset*, ModelData*>>& models, glm::vec3 point) {
    std::sort(models.begin(), models.end(),
        [&](std::tuple<MeshAsset*, MaterialAsset*, ModelData*> a, std::tuple<MeshAsset*, MaterialAsset*, ModelData*> b) -> bool {
            glm::vec3 posA = std::get<2>(a)->position;
            glm::vec3 posB = std::get<2>(b)->position;

            float distA = glm::distance(posA, point);
            float distB = glm::distance(posB, point);
            
            return distB < distA;
        }
    );
}

}

