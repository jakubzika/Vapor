#pragma once

#include <chrono>
#include <thread>


#include "../scene/Scene.h"
#include "../scene/SceneNode.h"
#include "../renderer/SceneRenderer.h"
#include "../input/UserInput.h"
#include "../window/Window.h"

namespace vpr {

// More unidiomatic to my goals
class Engine {

    public:
    Engine(Scene* scene, SceneRenderer* renderer, UserInputHandler* handler, Window* window);
    void loop();

    private:
    Scene *scene;
    SceneRenderer *renderer;
    UserInputHandler *inputHandler;
    Window *window;


};

}