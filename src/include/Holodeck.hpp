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
#include "TransformState.hpp"
#include "CameraState.hpp"

struct Model;
struct TextManager;

using namespace std;
namespace fs = std::filesystem;

class Holodeck
{
public:
	Holodeck();
	void render_loop();
	~Holodeck() { glfwTerminate(); }
	void render_models();
	void add_model(Model&& model);
	void attach_text_manager(TextManager&&);
	void generate_configs_from_json_dir(string directory);
	void updateModels();
	int generate_models_from_configs();
private:
	vector<Model> models;
    GLFWwindow *window;
	TextManager text_manager;
	vector<JsonConfig> world_configs;
	InputState inputState;
	TransformState transformState;
	CameraState cameraState;
    int init_window();
	bool is_initialized = false;
};

#endif