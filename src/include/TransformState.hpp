#ifndef TRANSFORM_STATE_H_
#define TRANSFORM_STATE_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputState.hpp"

struct TransformState {
    glm::mat4 model_mat;
    glm::mat4 rotate_about_x_axis;
    glm::mat4 rotate_about_y_axis;
    glm::mat4 rotate_about_z_axis;
    glm::mat4 translation_matrix;

    TransformState() : model_mat{glm::mat4(1.0f)} {}
    void update(const InputState& is);
};

#endif