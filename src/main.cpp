#include "Application.hpp"
#include "Program.hpp"
#include "Attributes.hpp"
#include "Cube.hpp"
#include "Vertex.hpp"

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

		float cube_center[3] = {0.0f, 0.0f, 0.0f};
		Cube cube(0.1, cube_center);
		AttributesDescriptor cube_attr {
			2,
			{3,2},
			{GL_FLOAT, GL_FLOAT, GL_FLOAT},
			{0, 3},
			{5, 5},
		};
		Mesh cube_mesh(&cube.vertices, &cube.indices, &cube_attr);

		TextureDescriptor text1_desc(program_cube.id, "texture1", "../res/textures/stallman.jpg", GL_RGB);
		TextureDescriptor text2_desc(program_cube.id, "texture2", "../res/textures/gnu.png", GL_RGBA);

		UniformDescriptor rotate_about_x_uniform(program_cube.id, "rotate_about_x");
		UniformDescriptor rotate_about_y_uniform(program_cube.id, "rotate_about_y");
		UniformDescriptor rotate_about_z_uniform(program_cube.id, "rotate_about_z");

		UniformDescriptor translate_uniform(program_cube.id, "translate");
		UniformDescriptor mixvalue_uniform(program_cube.id, "mixvalue");
		UniformDescriptor projection_uniform(program_cube.id, "projection");
		UniformDescriptor camera_uniform(program_cube.id, "look_at");

		cube_mesh.add_uniform(rotate_about_x_uniform);
		cube_mesh.add_uniform(rotate_about_y_uniform);
		cube_mesh.add_uniform(rotate_about_z_uniform);
		cube_mesh.add_uniform(translate_uniform);
		cube_mesh.add_uniform(mixvalue_uniform);
		cube_mesh.add_uniform(projection_uniform);
		cube_mesh.add_uniform(camera_uniform);

		cube_mesh.add_texture(texture1_desc);
		cube_mesh.add_texture(texture2_desc);

		Model cube_model();
		cube_model.add_mesh(cube_mesh);
		cube_model.attach_program(program_cube);
		app.add_model(cube_model);



		app.render_models();

	} catch (std::exception &e) {
		std::cerr<<"Application error! "<<e.what()<<std::endl;
		return -1;
	}

	return 0;
}
