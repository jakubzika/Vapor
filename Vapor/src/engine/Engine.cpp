

#include "../../include/Types.h"
#include "../../include/engine/Engine.h"

namespace vpr {

Engine::Engine(Scene* scene, SceneRenderer* renderer, UserInputHandler* handler, Window* window) {
    this->scene = scene;
    this->renderer = renderer;
    this->inputHandler = handler;
    this->window = window;
}

void Engine::loop() {

    bool quit = false;

    while(!this->inputHandler->getUserInput()->deltaKeyPressed[KeyEnum::VPR_KEY_ESC]) {
        glutMainLoopEvent();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->scene->updateData();
        this->renderer->render();

        glutSwapBuffers();
        this->inputHandler->tick();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

}