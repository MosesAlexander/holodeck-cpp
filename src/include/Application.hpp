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

using namespace std;

class Application
{
public:
	Application();
	void render_loop();
	~Application() { glfwTerminate(); }
	void render_models();
private:
    GLFWwindow *window;
    int init_window();
	void process_input();
	bool is_initialized = false;
};

class application_exception: public std::runtime_error {
public:
	application_exception(std::string const &msg): std::runtime_error(msg) {}
};

#endif