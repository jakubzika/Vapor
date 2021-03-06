/**
 * \file       SceneCamre.h
 * \author     Jakub Zíka
 * \date       2020/20/5
 * \brief      description
 *
 *  Camera in scene
 *
*/

#pragma once

#include "pgr.h"

#include "SceneObject.h"

namespace vpr {


struct CameraData {
    glm::mat4 view;
    glm::mat4 viewNormals;

    glm::mat4 projection;
    
    glm::vec3 position;
};

class SceneCamera : SceneObject{
    public:

    SceneCamera();

    void updateView();
    void updateProjection();

    void lookAt(glm::vec3 position,glm::vec3 center,glm::vec3 up);

    void setPosition(glm::vec3 position);
    void setCenter(glm::vec3 center);
    void setUp(glm::vec3 up);
    void setCamera(glm::vec3 position ,glm::vec3 center, glm::vec3 up);
    void setWindowSize(int width,int height);
    void setFOV(float FOV);

    glm::vec3 getPosition() {return position;}
    glm::vec3 getCenter() {return center;}
    glm::vec3 getUp() {return up;}

    
    CameraData* getCameraData();

    private:

    int width;
    int height;
    float FOV{60.0};

    CameraData data;

    glm::vec3 position{0.0,0.0,0.0};
    glm::vec3 center{0.0,0.0,1.0};
    glm::vec3 up{0.0,1.0,0.0};

    

};

}