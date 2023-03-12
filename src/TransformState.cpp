#include "TransformState.hpp"


void TransformState::update(const InputState& is) {
    rotate_about_x_axis = glm::rotate(model_mat, M_PIf * is.x_angle_multiplier, glm::vec3(1.0f, 0.0f, 0.0f));
    rotate_about_y_axis = glm::rotate(model_mat, M_PIf * is.y_angle_multiplier, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate_about_z_axis = glm::rotate(model_mat, M_PIf * is.z_angle_multiplier, glm::vec3(0.0f, 0.0f, 1.0f));
    translation_matrix = glm::translate(model_mat, glm::vec3(is.cur_off_x, is.cur_off_y, is.cur_off_z));
}
