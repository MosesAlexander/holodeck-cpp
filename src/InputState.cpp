#include "InputState.hpp"

void InputState::process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

    glfwGetCursorPos(window, &current_cursor_x, &current_cursor_y);

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		moving_in = true;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
		moving_in = false;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera_moving_forwards = true;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
		camera_moving_forwards = false;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera_moving_backwards = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
		camera_moving_backwards = false;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera_moving_left = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		camera_moving_left = false;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera_moving_right = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		camera_moving_right = false;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera_moving_down = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
		camera_moving_down = false;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera_moving_up = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
		camera_moving_up = false;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		moving_out = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE) {
		moving_out = false;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		moving_up = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
		moving_up = false;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		moving_down = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		moving_down = false;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		moving_left = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
		moving_left = false;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		moving_right = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
		moving_right = false;
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		reset_all_angles = true;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE) {
		reset_all_angles = false;
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		x_rot_cwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE) {
		x_rot_cwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		x_rot_ccwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE) {
		x_rot_ccwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		y_rot_cwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
		y_rot_cwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		y_rot_ccwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
		y_rot_ccwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		z_rot_cwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) {
		z_rot_cwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		z_rot_ccwise = true;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) {
		z_rot_ccwise = false;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS) {
		mixvalue_grow = true;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_RELEASE) {
		mixvalue_grow = false;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS) {
		mixvalue_shrink = true;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_RELEASE) {
		mixvalue_shrink = false;
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

    update();
}

void InputState::update() {
    if (moving_in == true) {
        cur_off_z += 0.02f;
    }
    if (moving_out == true) {
        cur_off_z -= 0.02f;
    }
    if (moving_down == true) {
        cur_off_y -= 0.02f;
    }
    if (moving_up == true) {
        cur_off_y += 0.02f;
    }
    if (moving_left == true) {
        cur_off_x -= 0.02f;
    }
    if (moving_right == true) {
        cur_off_x += 0.02f;
    }

    if (x_rot_ccwise == true) {
        x_angle_multiplier += 0.01f;
    }
    if (x_rot_cwise == true) {
        x_angle_multiplier -= 0.01f;
    }

    if (y_rot_ccwise == true) {
        y_angle_multiplier += 0.01f;
    }
    if (y_rot_cwise == true) {
        y_angle_multiplier -= 0.01f;
    }

    if (z_rot_ccwise == true) {
        z_angle_multiplier += 0.01f;
    }
    if (z_rot_cwise == true) {
        z_angle_multiplier -= 0.01f;
    }

    if (reset_all_angles == true) {
        x_angle_multiplier = 0.0f;
        y_angle_multiplier = 0.0f;
        z_angle_multiplier = 0.0f;
    }

    if (mixvalue_grow == true) {
        mixvalue += 0.02f;
    }

    if (mixvalue_shrink == true) {
        mixvalue -= 0.02f;
    }

    float cursor_x_diff = last_cursor_x - current_cursor_x;
    last_cursor_x = current_cursor_x;
    float cursor_y_diff = last_cursor_y - current_cursor_y;
    last_cursor_y = current_cursor_y;

    yaw -= 0.03f * cursor_x_diff;
    pitch += 0.03f * cursor_y_diff;

    if (pitch < -89.95f) {
        pitch = -89.95f;
    }
    if (pitch > 89.95f) {
        pitch = 89.95f;
    }

}