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
	window = glfwCreateWindow(1920, 1080, "MyOpenGL", NULL, NULL);
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

	glViewport(0, 0, 1920, 1080);
	glClearColor(0.2f,0.3f,0.3f,1.0f);

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
			glm::radians(fov_val), 1024.0f / 768.0f, 0.1f, 100.0f);

	models[0].meshes[0].uniforms[5].update(
		std::move(
			UniformPackedParam{
				type: uniform_type::Uniform4FVMatrix,
				parammat: std::move(perspective_projection_matrix)
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

		if (zoom_in == true) {
			if (fov_val > 0.0f) {
				fov_val -= 0.2f;
			}
		} 

		if (zoom_out == true) {
			if (fov_val < 360.0f) {
				fov_val += 0.2f;
			}
		}

		if (reset_zoom == true) {
			fov_val = 45.0f;
		}

		if (zoom_out == true || zoom_in == true || reset_zoom == true) {
			models[0].use_program();

			glm::mat4 perspective_projection_matrix = glm::perspective(
					glm::radians(fov_val), 1024.0f / 768.0f, 0.1f, 100.0f);

			models[0].meshes[0].uniforms[5].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(perspective_projection_matrix)
					}
				)
			);
		}

		auto model = glm::mat4(1.0f);
		auto rotate_about_x_axis = glm::rotate(model, M_PIf * x_angle_multiplier, glm::vec3(1.0f, 0.0f, 0.0f));
		auto rotate_about_y_axis = glm::rotate(model, M_PIf * y_angle_multiplier, glm::vec3(0.0f, 1.0f, 0.0f));
		auto rotate_about_z_axis = glm::rotate(model, M_PIf * z_angle_multiplier, glm::vec3(0.0f, 0.0f, 1.0f));
		auto translation_matrix = glm::translate(model, glm::vec3(cur_off_x, cur_off_y, cur_off_z));


		if (mixvalue_grow == true) {
			mixvalue += 0.02f;
		}

		if (mixvalue_shrink == true) {
			mixvalue -= 0.02f;
		}

		glfwGetCursorPos(window, &current_cursor_x, &current_cursor_y);

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

		// Gram-Schmidt process
		// Positive Z axis leads outside the screen
		auto direction = glm::vec3(0.0f, 0.0f, 0.0f);
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		auto camera_front = glm::normalize(direction);

		if (camera_moving_forwards == true) {
			camera_position += camera_front * 0.02f;
		}

		if (camera_moving_backwards == true) {
			camera_position -= camera_front * 0.02f;
		}

		camera_position.y= 0.2f;

		auto camera_target = camera_position + camera_front;
		auto camera_direction = glm::normalize(camera_position - camera_target);
		auto c_up = glm::vec3(0.0f, 1.0f, 0.0f);
		auto camera_right = glm::normalize(glm::cross(c_up, camera_direction));
		auto camera_up = glm::cross(camera_direction, camera_right);

		if (camera_moving_left == true) {
			camera_position -= camera_right * 0.009f;
		}

		if (camera_moving_right == true) {
			camera_position += camera_right * 0.009f;
		}

		if (camera_moving_down == true) {
			camera_position.y -= 0.02f;
			if (camera_position.y < 0.2f) {
				camera_position.y = 0.2f;
			}
		}

		if (camera_moving_up == true) {
			camera_position.y += 0.02f;
		}

		//auto LookAt = glm::lookAt(camera_position, camera_direction, camera_up);
		auto mat_A = glm::mat4(
			glm::vec4(camera_right, 0.0f),
			glm::vec4(camera_up, 0.0f),
			glm::vec4(camera_direction, 0.0f),
			glm::vec4(0.0f,0.0f,0.0f,1.0f)
		);

		mat_A = glm::transpose(mat_A);
		auto mat_B = glm::mat4(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(-camera_position, 1.0f)
		);

		auto LookAt = mat_A * mat_B;

		models[0].use_program();

		models[0].meshes[0].textures[0].set_active_texture(0);
		models[0].meshes[0].textures[1].set_active_texture(1);

		for (auto& mesh : models[0].meshes) {
			mesh.uniforms[0].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(rotate_about_x_axis)
					}
				)
			);
			mesh.uniforms[1].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(rotate_about_y_axis)
					}
				)
			);
			mesh.uniforms[2].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(rotate_about_z_axis)
					}
				)
			);
			mesh.uniforms[3].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(translation_matrix)
					}
				)
			);
			mesh.uniforms[4].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform1FParam,
						param1f: mixvalue
					}
				)
			);
			mesh.uniforms[6].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(LookAt)
					}
				)
			);

			mesh.uniforms[7].update(
				UniformPackedParam{
					type: uniform_type::Uniform3FParam,
					param3f: {1.0f, 1.0f, 1.0f}
				}
			);

			mesh.bind_vao();
			mesh.render();
		}

		for (auto model_idx = 1; model_idx < (models.size() - 1); model_idx++) {
			models[model_idx].use_program();
			for (auto& mesh : models[model_idx].meshes) {
				mesh.bind_vao();
				if (mesh.textures.size() > 0)
					mesh.textures[0].set_active_texture(0);

				mesh.uniforms[0].update(
					std::move(
						UniformPackedParam{
							type: uniform_type::Uniform4FVMatrix,
							parammat: std::move(perspective_projection_matrix)
						}
					)
				);

				mesh.uniforms[1].update(
					std::move(
						UniformPackedParam{
							type: uniform_type::Uniform4FVMatrix,
							parammat: std::move(LookAt)
						}
					)
				);

				mesh.uniforms[2].update(
					std::move(
						UniformPackedParam{
							type: uniform_type::Uniform3FParam,
							param3f: {1.0f, 1.0f, 1.0f}
						}
					)
				);
			}
			models[model_idx].render();
		}

		// Light cube
		models[7].use_program();

		for (auto& mesh : models[7].meshes) {
			mesh.uniforms[0].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(glm::mat4(1.0f))
					}
				)
			);
			mesh.uniforms[1].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(glm::mat4(1.0f))
					}
				)
			);
			mesh.uniforms[2].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(glm::mat4(1.0f))
					}
				)
			);
			mesh.uniforms[3].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(glm::mat4(1.0f))
					}
				)
			);
			mesh.uniforms[4].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(perspective_projection_matrix)
					}
				)
			);
			mesh.uniforms[5].update(
				std::move(
					UniformPackedParam{
						type: uniform_type::Uniform4FVMatrix,
						parammat: std::move(LookAt)
					}
				)
			);

			mesh.bind_vao();
			mesh.render();
		}

		//text_manager.render_text(string("Greetings mortals"), 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
		
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

void Application::attach_text_manager(TextManager&& text_manager) {
	this->text_manager = std::move(text_manager);
}

void Application::generate_configs_from_json_dir(string dir_path)
{
    for (const auto & entry : fs::directory_iterator(dir_path))
    {
		std::string config_path(entry.path());
        std::cout << "Found config file: " << config_path << std::endl;

		world_configs.push_back(JsonConfig(config_path));
    }
}

GLenum parse_shader_type(string shader_type)
{
	if (shader_type == "VERTEX_SHADER")
		return GL_VERTEX_SHADER;
	if (shader_type == "FRAGMENT_SHADER")
		return GL_FRAGMENT_SHADER;
	
	cerr<<"ERROR: unrecognized shader type!"<<endl;
	return 0x0;
}

GLenum parse_gl_type(string gl_type) {
	if (gl_type == "GL_FLOAT")
		return GL_FLOAT;
	if (gl_type == "GL_UINT")
		return GL_UNSIGNED_INT;
	if (gl_type == "RGB")
		return GL_RGB;
	if (gl_type == "RGBA")
		return GL_RGBA;

	cerr<<"ERROR: unrecognized GL type!"<<endl;
	return 0;
}

uniform_type parse_uniform_type(string type_str) {
	if (type_str == "mat4f")
		return uniform_type::Uniform4FVMatrix;
	if (type_str == "float1")
		return uniform_type::Uniform1FParam;
	if (type_str == "vec3f")
		return uniform_type::Uniform3FParam;
	if (type_str == "int1")
		return uniform_type::Uniform1IParam;
	
	return uniform_type::Undefined;
}

int Application::generate_models_from_configs() {
	for (auto json_conf : world_configs) {
		vector<float> vertices;
		vector<GLuint> indices;
		
		switch(json_conf.get_object_type())
		{
			case object_type::Cube:
			{
				auto center_vec = json_conf.mData["attributes"]["center"].get<vector<float>>();
				float side_length = json_conf.mData["attributes"]["side_length"].get<float>();
				Cube cube(side_length, center_vec.data());
				vertices = cube.vertices;
				indices = cube.indices;

				break;
			}
			case object_type::None:
			{
				cerr << "Error, object type not supported" << endl;
				return -1;
				break;
			}
		}

		cout << "Found a cube"<<endl;
		vector<Shader> shaders;
		for (auto &shader_json : json_conf.mData["resources"]["shaders"])
		{
			cout << "Shader found: " << shader_json["filepath"] << " shader type: " << shader_json["shader_type"] << endl;
			Shader shader(shader_json["filepath"].get<string>().c_str(), parse_shader_type(shader_json["shader_type"]));
			shaders.push_back(std::move(shader));
		}
		Program program;

		for (auto &shader : shaders) {
			program.add_shader(&shader);
		}

		int ret = program.link_shaders();
		if (ret < 0) {
			cerr << "There was a problem linking the cube shaders!" << endl;
			return -1;
		}


		unsigned int component_groups = json_conf.mData["attributes"]["component_groups"].get<unsigned int>();
		vector<int> component_nums = json_conf.mData["attributes"]["component_nums"].get<vector<int>>();
		vector<string> component_types_strings = json_conf.mData["attributes"]["component_types"].get<vector<string>>();
		vector<uint32_t> component_offsets = json_conf.mData["attributes"]["component_offsets"].get<vector<uint32_t>>();
		vector<int> component_strides = json_conf.mData["attributes"]["component_strides"].get<vector<int>>();
		vector<GLenum> component_types;

		for (auto &type_str : component_types_strings) {
			component_types.push_back(parse_gl_type(type_str));
		}

		AttributesDescriptor attr {
			component_groups,
			component_nums,
			component_types,
			component_offsets,
			component_strides
		};

		Mesh mesh(&vertices, &indices, &attr);
		vector<TextureDescriptor> textures;
		for (auto &texture_json : json_conf.mData["resources"]["textures"])
		{
			TextureDescriptor text_desc(
				program.id,
				texture_json["name"].get<string>().c_str(),
				texture_json["path"].get<string>().c_str(),
				parse_gl_type(texture_json["format"].get<string>()));
			mesh.add_texture(std::move(text_desc));
		}

		for (auto &uniform_json : json_conf.mData["resources"]["uniforms"]) {
			UniformDescriptor uniform_desc(
				program.id,
				uniform_json["uniform_name"].get<string>().c_str(),
				parse_uniform_type(uniform_json["uniform_type"].get<string>())
			);
			mesh.add_uniform(std::move(uniform_desc));
		}

		Model model;
		model.add_mesh(std::move(mesh));
		model.attach_program(&program);
		
		add_model(std::move(model));

	}

	return 0;
}
