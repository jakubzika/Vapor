/**
 * \file       Util.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Util functions
 *
*/

#pragma once

#include "pgr.h"
#include "./Types.h"
#include "./scene/ModelEntity.h"
#include <algorithm>  

namespace vpr {

/**
 * @brief Get the Model Type object
 * 
 * @param type 
 * @return ModelType 
 */
ModelType getModelType(std::string type);

/**
 * @brief Sorts models according to euclidean distance, from furthest
 * 
 */
void sortByDistanceFromPoint(std::vector<std::tuple<MeshAsset*, MaterialAsset*, ModelData*>>&, glm::vec3);
}
