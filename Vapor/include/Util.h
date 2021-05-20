#pragma once

#include "pgr.h"
#include "./Types.h"
#include "./scene/ModelEntity.h"
#include <algorithm>  

namespace vpr {

ModelType getModelType(std::string type);

void sortByDistanceFromPoint(std::vector<std::tuple<MeshAsset*, MaterialAsset*, ModelData*>>&, glm::vec3);
}
