#include "Application.hpp"
#include "Program.hpp"

int main() {
	try {
		Application app;
		int ret = 0;

		Shader vert_shader_cube("src/shaders/cube.vert", GL_VERTEX_SHADER);
		Shader frag_shader_cube("src/shaders/cube.frag", GL_FRAGMENT_SHADER);

		Program program_cube;

		program_cube.add_shader(&vert_shader_cube);
		program_cube.add_shader(&frag_shader_cube);
		ret = program_cube.link_shaders();
		if (ret < 0) {
			cerr<<"There was a problem compiling the shaders!"<<endl;
			return -1;
		}

		app.render_models();

	} catch (std::exception &e) {
		std::cerr<<"Application error! "<<e.what()<<std::endl;
		return -1;
	}

	return 0;
}
