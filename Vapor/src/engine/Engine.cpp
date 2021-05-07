

#include "../../include/Types.h"
#include "../../include/engine/Engine.h"

namespace vpr {

Engine::Engine(Scene* scene, UserInputHandler* handler, Window* window) {
    this->scene = scene;
    
    this->inputHandler = handler;
    this->window = window;
}

void Engine::init() {
    this->scene->gatherRenderingData(renderer);
    scene->updateData();

    // glutMainLoop();
}



void Engine::registerAction(IAction* action) {
    this->actions.push_back(action);
}

void Engine::processActions() {
    for(auto& action: this->actions) {
        action->tick(0);
    }
}

void Engine::loop() {
    std::cout << "Starting main loop\n";
    bool quit = false;
    
    glutMainLoopEvent();

    while(!this->inputHandler->getUserInput()->deltaKeyPressed[KeyEnum::VPR_KEY_ESC]) {
        this->inputHandler->postTick();

        glutMainLoopEvent();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->processActions();
        

        this->scene->updateData();
        this->renderer.render();

        glutSwapBuffers();

        this->inputHandler->tick();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

}