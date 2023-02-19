#ifndef APP_HEADERFILE_H
#define APP_HEADERFILE_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <numbers>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.hpp"
#include "BufferDescriptor.hpp"
#include "EboDescriptor.hpp"
#include "Attributes.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "TextManager.hpp"
#include "Exception.hpp"
#include "JsonConfig.hpp"
#include <filesystem>

struct Model;
struct TextManager;

using namespace std;
namespace fs = std::filesystem;

class Application
{
public:
	Application();
	void render_loop();
	~Application() { glfwTerminate(); }
	void render_models();
	void add_model(Model&& model);
	void attach_text_manager(TextManager&&);
	void generate_configs_from_json_dir(string directory);
	int generate_models_from_configs();
private:
    GLFWwindow *window;
	vector<Model> models;
	TextManager text_manager;
	vector<JsonConfig> world_configs;
    int init_window();
	void process_input(
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
	);
	bool is_initialized = false;
};

#endif