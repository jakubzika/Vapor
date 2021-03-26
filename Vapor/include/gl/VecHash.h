#pragma once

#include "pgr.h"

namespace vpr {

struct KeyFuncs
{
    size_t operator()(const glm::tvec3<unsigned int>& k)const
    {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y) ^ std::hash<int>()(k.z);
    }

    bool operator()(const glm::vec3& a, const glm::vec3& b)const
    {
            return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

}
