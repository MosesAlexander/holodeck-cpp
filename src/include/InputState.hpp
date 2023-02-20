#ifndef INPUTSTATE_HEADERFILE_H
#define INPUTSTATE_HEADERFILE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct InputState {
	float cur_off_x = 0.0f;
	float cur_off_y = 0.0f;
	float cur_off_z = -0.4f;
	float camera_cur_off_x = 0.0f;
	float camera_cur_off_y = 0.2f;
	float camera_cur_off_z = 2.0f;
	float x_angle_multiplier = 0.0f;
	float y_angle_multiplier = 0.0f;
	float z_angle_multiplier = 0.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;

	double last_cursor_x = 960.0;
	double last_cursor_y = 540.0;
	double current_cursor_x = 0.0;
	double current_cursor_y = 0.0;

	float fov_val = 45.0f;
	float mixvalue = 0.5f;

	bool moving_up = false;
	bool moving_down = false;
	bool moving_left = false;
	bool moving_right = false;
	bool moving_in = false;
	bool moving_out = false;
	bool camera_moving_up = false;
	bool camera_moving_down = false;
	bool camera_moving_left = false;
	bool camera_moving_right = false;
	bool camera_moving_forwards = false;
	bool camera_moving_backwards = false;
	bool x_rot_cwise = false;
	bool x_rot_ccwise = false;
	bool y_rot_cwise = false;
	bool y_rot_ccwise = false;
	bool z_rot_cwise = false;
	bool z_rot_ccwise = false;
	bool reset_all_angles = false;
	bool mixvalue_grow = false;
	bool mixvalue_shrink = false;

    void process_input(GLFWwindow *);
    void update();
};

#endif