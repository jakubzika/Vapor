#include "../../include/input/GLUTKeyMapping.h"

namespace vpr {

KeyEnum charToKey(char key) {
    return GLUTCharKeyMapping[key];
}

KeyEnum specialToKey(int key) {
    return GLUTSpecialKeyMapping[key];
}

}