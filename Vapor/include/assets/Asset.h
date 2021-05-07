#pragma once

#include <iostream>

#include "../nlohmann/json.hpp"
#include "../Types.h"

using json = nlohmann::json;

namespace vpr {

class Asset {
  public:
    Asset();
    virtual bool loadFromPath(const std::string &path);
    // virtual bool loadFromConfiguration(json confifuration);

    // virtual bool loadFromBuffer(void * data,std::size_t dataSize);

    // void reload(); // TODO: implement

    AssetTypeId getId();
  private:

  protected:  
    std::string path;
    AssetTypeId id;
};

}