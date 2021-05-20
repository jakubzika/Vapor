#pragma once

#include <iostream>

#include "../nlohmann/json.hpp"
#include "../Types.h"

using json = nlohmann::json;

namespace vpr {

enum AssetType {
  FILE_ASSET,
  HARDCODED_ASSET
};

class Asset {
  public:
    Asset();

    virtual bool load(std::string path);
    // virtual bool loadFromConfiguration(json confifuration);

    // virtual bool loadFromBuffer(void * data,std::size_t dataSize);

    // void reload(); // TODO: implement
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