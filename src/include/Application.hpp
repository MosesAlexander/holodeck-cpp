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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.hpp"
#include "BufferDescriptor.hpp"
#include "EboDescriptor.hpp"
#include "Attributes.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

struct Model;

using namespace std;

class Application
{
public:
	Application();
	void render_loop();
	~Application() { glfwTerminate(); }
	void render_models();
	void add_model(Model&& model);
private:
    GLFWwindow *window;
	vector<Model> models;
    int init_window();
	void process_input();
	bool is_initialized = false;
};

class application_exception: public std::runtime_error {
public:
	application_exception(std::string const &msg): std::runtime_error(msg) {}
};

#endif