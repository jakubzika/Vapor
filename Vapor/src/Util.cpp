#include "../include/Util.h"

namespace vpr {

ModelType getModelType(std::string type) {
    if(type == "SOLID") return SOLID;
    else if(type =="TEXTURED") return TEXTURED;
    
    return UNKNOWN;
}

}

