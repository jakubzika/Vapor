#pragma once

#include <chrono>
#include <thread>


#include "../scene/Scene.h"
#include "../scene/SceneNode.h"
#include "../renderer/SceneRenderer.h"
#include "../input/UserInput.h"
#include "../window/Window.h"
#include "../action/IAction.h"

namespace vpr {

// More unidiomatic to my goals
class Engine : public IWindowRenderer{

    public:
    Engine(Scene* scene, UserInputHandler* handler, Window* window);
    void loop();
    void init();

    void registerAction(IAction* action);

    private:
    void processActions();

    std::vector<IAction*> actions;
    Scene *scene;
    SceneRenderer renderer;
    UserInputHandler *inputHandler;
    Window *window;


};

}