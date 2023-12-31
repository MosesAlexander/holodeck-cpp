#include "Holodeck.hpp"
#include "Program.hpp"
#include "Attributes.hpp"
#include "Cube.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Quad.hpp"

int main() {
	try {
		Holodeck deck;
		int ret = 0;

		deck.generate_configs_from_json_dir("res/configs/");
		ret = deck.generate_models_from_configs();
		if (ret < 0) {
			cerr << "Error generating models from configs"<<endl;
			return -1;
		}

		// Text manager setup
		Shader vert_shader_text("src/shaders/text.vert", GL_VERTEX_SHADER);
		Shader frag_shader_text("src/shaders/text.frag", GL_FRAGMENT_SHADER);

		Program program_text;
		program_text.add_shader(&vert_shader_text);
		program_text.add_shader(&frag_shader_text);

		ret = program_text.link_shaders();
		if (ret < 0) {
			cerr<<"There was a problem linking the text shaders"<<endl;
			return -1;
		}

		TextManager text_manager(&program_text);

		deck.attach_text_manager(std::move(text_manager));

		deck.render_models();
	} catch (std::exception &e) {
		std::cerr<<"Holodeck error! "<<e.what()<<std::endl;
		return -1;
	}

	return 0;
}
