/**
 * \file       Engine.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Engine  orchestrates data preparation for rendering and the loop itself
 *  and managing registerable action plugins with custom functionality
 *
*/

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

    /**
     * @brief Registers new action
     * 
     * @param action 
     */
    void registerAction(IAction* action);
    
    SceneRenderer* getRenderer();

    private:
    void processActions();

    std::vector<IAction*> actions;
    Scene *scene;
    SceneRenderer renderer;
    UserInputHandler *inputHandler;
    Window *window;


};

}