#include "application.hpp"

int main() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "holodeck", NULL, NULL);
	if (window == NULL) {
		std::cout<< "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	return 0;
}
