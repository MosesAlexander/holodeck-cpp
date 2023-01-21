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

	glm::mat4 perspective_projection_matrix = glm::perspective(glm::radians(fov_val), 1024.0f / 768.0f, 0.0f, 100.0f);

	models[0].meshes[0].uniforms[5].update(std::move(UniformPackedParam{type: uniform_type::Uniform4FVMatrix, parammat: perspective_projection_matrix}));
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		process_input();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::process_input() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Application::add_model(Model&& model) {
	models.push_back(std::move(model));
}