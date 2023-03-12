#include "CameraState.hpp"

void CameraState::update(const InputState &is) {
    // Gram-Schmidt process
    // Positive Z axis leads outside the screen
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
    direction.x = cos(glm::radians(is.yaw)) * cos(glm::radians(is.pitch));
    direction.y = sin(glm::radians(is.pitch));
    direction.z = sin(glm::radians(is.yaw)) * cos(glm::radians(is.pitch));

    camera_front = glm::normalize(direction);

    if (is.camera_moving_forwards == true) {
        camera_position += camera_front * 0.02f;
    }

    if (is.camera_moving_backwards == true) {
        camera_position -= camera_front * 0.02f;
    }

    camera_position.y= 0.2f;

    camera_target = camera_position + camera_front;
    camera_direction = glm::normalize(camera_position - camera_target);
    c_up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_right = glm::normalize(glm::cross(c_up, camera_direction));
    camera_up = glm::cross(camera_direction, camera_right);

    if (is.camera_moving_left == true) {
        camera_position -= camera_right * 0.009f;
    }

    if (is.camera_moving_right == true) {
        camera_position += camera_right * 0.009f;
    }

    if (is.camera_moving_down == true) {
        camera_position.y -= 0.02f;
        if (camera_position.y < 0.2f) {
            camera_position.y = 0.2f;
        }
    }

    if (is.camera_moving_up == true) {
        camera_position.y += 0.02f;
    }

    //LookAt = glm::lookAt(camera_position, camera_direction, camera_up);
    mat_A = glm::mat4(
        glm::vec4(camera_right, 0.0f),
        glm::vec4(camera_up, 0.0f),
        glm::vec4(camera_direction, 0.0f),
        glm::vec4(0.0f,0.0f,0.0f,1.0f)
    );

    mat_A = glm::transpose(mat_A);
    mat_B = glm::mat4(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4(-camera_position, 1.0f)
    );

    LookAt = mat_A * mat_B;
}

void CameraState::setInitialPos(const InputState &is) {
    camera_position = glm::vec3(is.camera_cur_off_x, is.camera_cur_off_y, is.camera_cur_off_z);
}