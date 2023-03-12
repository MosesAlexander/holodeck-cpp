#ifndef CAMERA_STATE_H_
#define CAMERA_STATE_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "InputState.hpp"

struct CameraState {
    glm::vec3 direction;
    glm::vec3 camera_front;
    glm::vec3 camera_target;
    glm::vec3 camera_direction;
    glm::vec3 camera_position;
    glm::vec3 c_up;
    glm::vec3 camera_right;
    glm::vec3 camera_up;
    glm::mat4 mat_A;
    glm::mat4 mat_B;
    glm::mat4 LookAt;
    glm::mat4 perspective_projection_matrix;

    CameraState() :
        direction{glm::vec3(0.0f, 0.0f, 0.0f)},
        perspective_projection_matrix{glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f)}
        {}
    void update(const InputState &is);
    void setInitialPos(const InputState &is);
};

#endif