/**
 * \file       Asset.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Abstrat asset definition
 * 
 * Each asset defines its configuration, whose values must json asset definition files contain
 *
*/

#pragma once

#include <iostream>

#include "../nlohmann/json.hpp"
#include "../Types.h"

using json = nlohmann::json;

namespace vpr {


// unused, still afraid to delete
enum AssetType {
  FILE_ASSET,
  HARDCODED_ASSET
};

class Asset {
  public:
    Asset();

    /**
     * @brief Loads asset with specified name
     * 
     * @param path asset name, must be present in AssetHandler
     * @return true 
     * @return false 
     */
    virtual bool load(std::string path);


    AssetType getType() {return assetType;}


    AssetTypeId getId() { return id;}
    void setId(AssetTypeId id) {this->id = id;}

  private:

  protected:  
    std::string path;
    AssetTypeId id;

    AssetType assetType{FILE_ASSET};
};

}