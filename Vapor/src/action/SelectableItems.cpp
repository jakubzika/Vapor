#include "../../include/action/SelectableItems.h"

namespace vpr {

#define WATER_RISING_LENGTH 1000
#define WATER_LOW -0.344 
#define WATER_HIGH -0.086

SelectableItems::SelectableItems(UserInput* input,SceneRenderer* renderer, ModelEntity* activator,std::vector<SceneEntity*> toHide, SceneEntity* waterLevel){
    std::cout << "Initalizing selectable items\n";
    this->input = input;

    this->activator = activator;
    this->toHide = toHide;
    this->waterLevel = waterLevel;

    this->renderer = renderer;
    
    timeInState = 0;
    stateTimeoutBlock = 0;
    state = STATE_EMPTY;

    for(auto item : toHide) {
        item->hide();
    }
}

void SelectableItems::tick(long msec) {

    // waterEffects->
    Action incomingAction = ACTION_TIME_TICK;
    unsigned int objectId = 0;
    if(input->deltaLeftMouseButton && input->leftMouseButton ) {
        objectId = renderer->getHoveredObject();
        if(objectId) {
            if(objectId == activator->getId()) {
                std::cout << "clicked\n";
                incomingAction = ACTION_CLICKED;
            }
        }
    }




    switch(state) {
        case STATE_EMPTY:
                switch(incomingAction) {
                    case ACTION_CLICKED:
                    std::cout << "Handle empty state\n";
                    if(setState(STATE_FILLING_WATER,WATER_RISING_LENGTH)){
                    for(auto item: toHide) {
                        item->show();
                    }
                        std::cout << "Triggered water filling state\n";
                    }
                break;
                }
        break;
        case STATE_FILLING_WATER:
            if(setState(STATE_FILLED_WATER, 0)) {
                // water filled event
            }

        break;
        case STATE_FILLED_WATER:
            switch(incomingAction) {
                    case ACTION_CLICKED:
                    for(auto item: toHide) {
                        item->hide();
                    }
                    setState(STATE_EMPTYING_WATER,WATER_RISING_LENGTH);
                break;
                }

        break;
        case STATE_EMPTYING_WATER:
            if(setState(STATE_EMPTY, 0)) {
                // water filled event
            }

        break;
    }
    updateWaterPosition();
    timeInState++;
    stateTimeoutBlock -= stateTimeoutBlock > 0 ? 1 : 0;
}

void SelectableItems::updateWaterPosition() {
    float linearWaterPosition = 0.0;
    if(state == STATE_FILLING_WATER)
        linearWaterPosition = ((float)timeInState)/WATER_RISING_LENGTH;
    else if(state == STATE_EMPTYING_WATER) 
        linearWaterPosition = 1.0 - ((float)timeInState)/WATER_RISING_LENGTH;
    else if(state == STATE_EMPTY)
        linearWaterPosition = 0.0;
    else
        linearWaterPosition = 1.0;


    float unitWaterPosition = sin(66*linearWaterPosition)/66+linearWaterPosition;
    float waterPosition = unitWaterPosition*(WATER_HIGH - WATER_LOW) + WATER_LOW;

    activator->setRotation(3.14,0.0,sin(linearWaterPosition*4.0)*10.0);

    waterLevel->setPosition(0.0,waterPosition,0.0);

}

bool SelectableItems::setState(States state, int stateTimeoutBlock) {
    if(this->stateTimeoutBlock != 0) return false;
    this->timeInState = 0;
    this->stateTimeoutBlock = stateTimeoutBlock;
    std::cout << "State machine " << this->state << " -> " << state << std::endl;
    this->state = state;
    return true;
}

}