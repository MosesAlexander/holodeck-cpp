#ifndef APP_HEADERFILE_H
#define APP_HEADERFILE_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <numbers>
#include <map>
#include <filesystem>
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
#include "Cube.hpp"
#include "Quad.hpp"
#include "InputState.hpp"

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
	vector<Model> models;
private:
    GLFWwindow *window;
	TextManager text_manager;
	vector<JsonConfig> world_configs;
	InputState inputState;
    int init_window();
	bool is_initialized = false;
};

#endif