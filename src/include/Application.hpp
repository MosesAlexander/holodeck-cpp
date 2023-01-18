#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Application
{
public:
	Application();
	void render_loop();
	~Application() { glfwTerminate(); }
private:
    GLFWwindow *window;
    int init_window();
	bool is_initialized = false;
};

class application_exception: public std::runtime_error {
public:
	application_exception(std::string const &msg): std::runtime_error(msg) {}
};