#include "Application.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int Application::init_window() {
	int ret = 0;
	if (GL_TRUE != glfwInit()) {
		std::cerr<<"Error initializing!"<<std::endl;
		ret = -1;
		goto err;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1024, 768, "MyOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cerr<<"Failed to create GLFW window" <<std::endl;
		glfwTerminate();
		ret = -1;
		goto err;
	}

	// make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// GLAD manages function pointers for OpenGL, initialize it before calling any
	// OpenGL function, glfwGetProcAddress does the OS detection
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr<<"Failed to initialize GLAD"<<std::endl;
		ret = -1;
		goto err;
	}

	glViewport(0, 0, 1024, 768);

	// set callback so the glViewport re-adjust to window resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	is_initialized = true;
err:
	return ret;
}

Application::Application() {
	if(init_window()) {
		throw application_exception("Failed to initialize window");
	}
}

void Application::render_models() {
	float cur_off_x = 0.0f;
	float cur_off_y = 0.0f;
	float cur_off_z = -0.4f;
	float camera_cur_off_x = 0.0f;
	float camera_cur_off_y = 0.2f;
	float camera_cur_off_z = 2.0f;
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
	float x_angle_multiplier = 0.0f;
	float y_angle_multiplier = 0.0f;
	float z_angle_multiplier = 0.0f;
	bool x_rot_cwise = false;
	bool x_rot_ccwise = false;
	bool y_rot_cwise = false;
	bool y_rot_ccwise = false;
	bool z_rot_cwise = false;
	bool z_rot_ccwise = false;
	bool reset_all_angles = false;
	float yaw = -90.0f;
	float pitch = 0.0f;
	bool zoom_in = false;
	bool zoom_out = false;
	bool reset_zoom = false;
	float fov_val = 45.0f;

	bool mixvalue_grow = false;
	bool mixvalue_shrink = false;

	double last_cursor_x = 400.0;
	double last_cursor_y = 300.0;
	double current_cursor_x = 0.0;
	double current_cursor_y = 0.0;

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	models[0].use_program();

	glm::mat4 perspective_projection_matrix = glm::perspective(
			glm::radians(fov_val), 1024.0f / 768.0f, 0.0f, 100.0f);

	models[0].meshes[0].uniforms[5].update(
		std::move(
			UniformPackedParam{
				type: uniform_type::Uniform4FVMatrix,
				parammat: perspective_projection_matrix
			}
		)
	);

	auto camera_position = glm::vec3(camera_cur_off_x, camera_cur_off_y, camera_cur_off_z);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		process_input(
			moving_up,
			moving_down,
			moving_left,
			moving_right,
			moving_in,
			moving_out,
			x_rot_cwise,
			x_rot_ccwise,
			y_rot_cwise,
			y_rot_ccwise,
			z_rot_cwise,
			z_rot_ccwise,
			reset_all_angles,
			mixvalue_grow,
			mixvalue_shrink,
			camera_moving_forwards,
			camera_moving_backwards,
			camera_moving_down,
			camera_moving_up,
			camera_moving_left,
			camera_moving_right,
			zoom_in,
			zoom_out,
			reset_zoom
		);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::process_input(
	bool& moving_up,
	bool& moving_down,
	bool& moving_left,
	bool& moving_right,
	bool& moving_in,
	bool& moving_out,
	bool& x_rot_cwise,
	bool& x_rot_ccwise,
	bool& y_rot_cwise,
	bool& y_rot_ccwise,
	bool& z_rot_cwise,
	bool& z_rot_ccwise,
	bool& reset_all_angles,
	bool& mixvalue_grow,
	bool& mixvalue_shrink,
	bool& camera_moving_forwards,
	bool& camera_moving_backwards,
	bool& camera_moving_down,
	bool& camera_moving_up,
	bool& camera_moving_left,
	bool& camera_moving_right,
	bool& zoom_in,
	bool& zoom_out,
	bool& reset_zoom
)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

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

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		zoom_in = true;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_RELEASE) {
		zoom_in = false;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
		zoom_out = true;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE) {
		zoom_out = false;
	}

	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS) {
		reset_zoom = true;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_MULTIPLY) == GLFW_RELEASE) {
		reset_zoom = false;
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
}

void Application::add_model(Model&& model) {
	models.push_back(std::move(model));
}