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
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glm::mat4 perspective_projection_matrix = glm::perspective(
			glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

	auto camera_position = glm::vec3(inputState.camera_cur_off_x,
									inputState.camera_cur_off_y,
									inputState.camera_cur_off_z);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		inputState.process_input(window);

		auto model_mat = glm::mat4(1.0f);
		auto rotate_about_x_axis = glm::rotate(
			model_mat, M_PIf * inputState.x_angle_multiplier, glm::vec3(1.0f, 0.0f, 0.0f));
		auto rotate_about_y_axis = glm::rotate(
			model_mat, M_PIf * inputState.y_angle_multiplier, glm::vec3(0.0f, 1.0f, 0.0f));
		auto rotate_about_z_axis = glm::rotate(
			model_mat, M_PIf * inputState.z_angle_multiplier, glm::vec3(0.0f, 0.0f, 1.0f));
		auto translation_matrix = glm::translate(
			model_mat, glm::vec3(inputState.cur_off_x, inputState.cur_off_y, inputState.cur_off_z));


		// Gram-Schmidt process
		// Positive Z axis leads outside the screen
		auto direction = glm::vec3(0.0f, 0.0f, 0.0f);
		direction.x = cos(glm::radians(inputState.yaw)) * cos(glm::radians(inputState.pitch));
		direction.y = sin(glm::radians(inputState.pitch));
		direction.z = sin(glm::radians(inputState.yaw)) * cos(glm::radians(inputState.pitch));

		auto camera_front = glm::normalize(direction);

		if (inputState.camera_moving_forwards == true) {
			camera_position += camera_front * 0.02f;
		}

		if (inputState.camera_moving_backwards == true) {
			camera_position -= camera_front * 0.02f;
		}

		camera_position.y= 0.2f;

		auto camera_target = camera_position + camera_front;
		auto camera_direction = glm::normalize(camera_position - camera_target);
		auto c_up = glm::vec3(0.0f, 1.0f, 0.0f);
		auto camera_right = glm::normalize(glm::cross(c_up, camera_direction));
		auto camera_up = glm::cross(camera_direction, camera_right);

		if (inputState.camera_moving_left == true) {
			camera_position -= camera_right * 0.009f;
		}

		if (inputState.camera_moving_right == true) {
			camera_position += camera_right * 0.009f;
		}

		if (inputState.camera_moving_down == true) {
			camera_position.y -= 0.02f;
			if (camera_position.y < 0.2f) {
				camera_position.y = 0.2f;
			}
		}

		if (inputState.camera_moving_up == true) {
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

		for (auto& model : models) {
			model.use_program();
			switch(model.obj_type) {
			case object_type::Cube:
			{
				model.meshes[0].textures[0].set_active_texture(0);
				model.meshes[0].textures[1].set_active_texture(1);

				for (auto& mesh : model.meshes) {
					for (auto& uniform : mesh.uniforms) {
						switch(uniform.transf_type) {
						case transform_type::rotate_x:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: rotate_about_x_axis
									}
								)
							);
						}
						break;
						case transform_type::rotate_y:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: rotate_about_y_axis
									}
								)
							);
						}
						break;
						case transform_type::rotate_z:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: rotate_about_z_axis
									}
								)
							);
						}
						break;
						case transform_type::translate:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: translation_matrix
									}
								)
							);
						}
						break;
						case transform_type::mixvalue:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform1FParam,
										param1f: inputState.mixvalue
									}
								)
							);
						}
						break;
						case transform_type::projection:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: perspective_projection_matrix
									}
								)
							);
						}
						break;
						case transform_type::look_at:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: LookAt
									}
								)
							);
						}
						break;
						case transform_type::lightColor:
						{
							uniform.update(
								UniformPackedParam{
									type: uniform_type::Uniform3FParam,
									param3f: {1.0f, 1.0f, 1.0f}
								}
							);
						}
						break;
						}
					}

					mesh.bind_vao();
					mesh.render();
				}
			}
			break;
			case object_type::Wall:
			case object_type::Floor:
			{
				for (auto& mesh : model.meshes) {
					mesh.bind_vao();
					if (mesh.textures.size() > 0)
						mesh.textures[0].set_active_texture(0);

					for (auto& uniform: mesh.uniforms) {
						switch(uniform.transf_type) {
						case transform_type::projection:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: perspective_projection_matrix
									}
								)
							);
						}
						break;
						case transform_type::look_at:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: LookAt
									}
								)
							);
						}
						break;
						case transform_type::lightColor:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform3FParam,
										param3f: {1.0f, 1.0f, 1.0f}
									}
								)
							);
						}
						break;
						}
					}
				}
				model.render();
			}
			break;
			case object_type::LightCube:
			{
				for (auto& mesh : model.meshes) {
					for (auto& uniform : mesh.uniforms) {
						switch(uniform.transf_type) {
						case transform_type::rotate_x:
						case transform_type::rotate_y:
						case transform_type::rotate_z:
						case transform_type::translate:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: glm::mat4(1.0f)
									}
								)
							);
						}
						break;
						case transform_type::projection:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: perspective_projection_matrix
									}
								)
							);
						}
						break;
						case transform_type::look_at:
						{
							uniform.update(
								std::move(
									UniformPackedParam{
										type: uniform_type::Uniform4FVMatrix,
										parammat: LookAt
									}
								)
							);
						}
						break;
						}
					}

					mesh.bind_vao();
					mesh.render();
				}
			}
			break;
			}
		}

		//text_manager.render_text(string("Greetings mortals"), 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
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

transform_type parse_transform_type(string transf_type_str) {
	if (transf_type_str == "rotate_about_x")
		return transform_type::rotate_x;
	if (transf_type_str == "rotate_about_y")
		return transform_type::rotate_y;
	if (transf_type_str == "rotate_about_z")
		return transform_type::rotate_z;
	if (transf_type_str == "translate")
		return transform_type::translate;
	if (transf_type_str == "mixvalue")
		return transform_type::mixvalue;
	if (transf_type_str == "projection")
		return transform_type::projection;
	if (transf_type_str == "look_at")
		return transform_type::look_at;
	if (transf_type_str == "lightColor")
		return transform_type::lightColor;

	return transform_type::undefined;
}

int Application::generate_models_from_configs() {
	for (auto json_conf : world_configs) {
		vector<float> vertices;
		vector<GLuint> indices;

		switch(json_conf.get_object_type())
		{
			case object_type::Cube:
			case object_type::LightCube:
			{
				auto center_vec = json_conf.mData["attributes"]["center"].get<vector<float>>();
				float side_length = json_conf.mData["attributes"]["side_length"].get<float>();
				Cube cube(side_length, center_vec.data());
				vertices = cube.vertices;
				indices = cube.indices;
			}
			break;
			case object_type::Floor:
			{
				auto center_vec = json_conf.mData["attributes"]["center"].get<vector<float>>();
				auto floor_center_vec = json_conf.mData["attributes"]["floor_center_offset"].get<vector<float>>();
				auto scale_vec = json_conf.mData["attributes"]["scale_factor"].get<vector<float>>(); 
				ScaleFactor floor_scale_factor{scale_vec[0], scale_vec[1]};
				auto width = json_conf.mData["attributes"]["width"].get<float>(); 
				auto height = json_conf.mData["attributes"]["height"].get<float>(); 
				Quad floor{width, height, floor_center_vec.data(), center_vec.data(), floor_scale_factor};
				vertices = floor.vertices;
				indices = floor.indices;
			}
			break;
			case object_type::Wall:
			{
				auto width = json_conf.mData["attributes"]["width"].get<float>(); 
				auto height = json_conf.mData["attributes"]["height"].get<float>(); 
				auto scale_vec = json_conf.mData["attributes"]["scale_factor"].get<vector<float>>(); 
				auto wall_offset = json_conf.mData["attributes"]["wall_offset"].get<vector<float>>();
				Quad wall {
					width,
					height,
					wall_offset.data(),
					wall_offset.data(),
					ScaleFactor{scale_vec[0], scale_vec[1]}
				};
				vertices = wall.vertices;
				indices = wall.indices;
			}
			break;
			case object_type::None:
			{
				cerr << "Error, object type not supported" << endl;
				return -1;
			}
			break;
		}

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
				parse_uniform_type(uniform_json["uniform_type"].get<string>()),
				parse_transform_type(uniform_json["uniform_name"].get<string>())
			);
			mesh.add_uniform(std::move(uniform_desc));
		}

		Model model;
		model.model_name = json_conf.mData["object_name"].get<string>();
		model.obj_type = json_conf.get_object_type();
		model.add_mesh(std::move(mesh));
		model.attach_program(program);
		
		add_model(std::move(model));

	}

	return 0;
}
