#include "../../include/action/UserKeyAction.h"
#include <iostream>

namespace vpr {

UserKeyAction::UserKeyAction(UserInput* input) {
    this->input = input;
}

void UserKeyAction::tick(long msec) {
    if(input->deltaKeyPressed[VPR_KEY_F] && input->keyPressed[VPR_KEY_F]) {
        std::cout << "Fog switch\n";
        AppState::fog = !AppState::fog;
    }

    if(input->deltaKeyPressed[VPR_KEY_N] && input->keyPressed[VPR_KEY_N] && input->keyPressed[VPR_KEY_SHIFT]) {
        AppState::wireframe = !AppState::wireframe;
        if(AppState::wireframe) {
            std::cout << "Enabled wireframe mode\n";
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        } else {
            std::cout << "Disabled wireframe mode\n";
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL); 
        }
    }


}

}