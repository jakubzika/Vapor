#include "../../include/window/Window.h"

namespace vpr {

Window::Window(int width, int height) {
    this->size.width = width;
    this->size.height = height;
}

WindowSize Window::getWindowSize() {
    return this->size;
}

}