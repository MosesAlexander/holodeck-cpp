#include "Application.hpp"
#include "Program.hpp"
#include "Attributes.hpp"
#include "Cube.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Quad.hpp"

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
			cerr<<"There was a problem linking the cube shaders!"<<endl;
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

		TextureDescriptor text1_desc(program_cube.id, "texture1", "res/textures/stallman.jpg", GL_RGB);
		TextureDescriptor text2_desc(program_cube.id, "texture2", "res/textures/gnu.png", GL_RGBA);

		UniformDescriptor rotate_about_x_uniform(program_cube.id, "rotate_about_x");
		UniformDescriptor rotate_about_y_uniform(program_cube.id, "rotate_about_y");
		UniformDescriptor rotate_about_z_uniform(program_cube.id, "rotate_about_z");

		UniformDescriptor translate_uniform(program_cube.id, "translate");
		UniformDescriptor mixvalue_uniform(program_cube.id, "mixvalue");
		UniformDescriptor projection_uniform(program_cube.id, "projection");
		UniformDescriptor camera_uniform(program_cube.id, "look_at");
		UniformDescriptor light_color_uniform(program_cube.id, "lightColor");

		cube_mesh.add_uniform(std::move(rotate_about_x_uniform));
		cube_mesh.add_uniform(std::move(rotate_about_y_uniform));
		cube_mesh.add_uniform(std::move(rotate_about_z_uniform));
		cube_mesh.add_uniform(std::move(translate_uniform));
		cube_mesh.add_uniform(std::move(mixvalue_uniform));
		cube_mesh.add_uniform(std::move(projection_uniform));
		cube_mesh.add_uniform(std::move(camera_uniform));
		cube_mesh.add_uniform(std::move(light_color_uniform));

		cube_mesh.add_texture(std::move(text1_desc));
		cube_mesh.add_texture(std::move(text2_desc));

		Model cube_model;
		cube_model.add_mesh(std::move(cube_mesh));
		cube_model.attach_program(&program_cube);

		app.add_model(std::move(cube_model));

		Shader vert_shader_floor("src/shaders/floor.vert", GL_VERTEX_SHADER);
		Shader frag_shader_floor("src/shaders/floor.frag", GL_FRAGMENT_SHADER);

		Program program_floor;
		program_floor.add_shader(&vert_shader_floor);
		program_floor.add_shader(&frag_shader_floor);

		ret = program_floor.link_shaders();
		if (ret < 0) {
			cerr<<"There was a problem linking the floor shaders"<<endl;
			return -1;
		}

		float floor_center_offset[3] = {0.0f, 0.000001f, 0.0f};
		float floor_center[3] = {0.0f, 0.0f, 0.0f};
		ScaleFactor floor_scale_factor{10.0, 10.0};
		Quad floor{10.0f, 0.0f, floor_center_offset, floor_center, floor_scale_factor};
		AttributesDescriptor floor_attr {
			2,
			{3, 2},
			{GL_FLOAT, GL_FLOAT, GL_FLOAT},
			{0, 3},
			{5, 5},
		};
		Mesh floor_mesh(&floor.vertices, &floor.indices, &floor_attr);

		TextureDescriptor text_floor(program_floor.id, "texture1", "res/textures/concrete_floor.jpg", GL_RGB);

		projection_uniform = UniformDescriptor(program_floor.id, "projection");
		camera_uniform = UniformDescriptor(program_floor.id, "look_at");
		light_color_uniform = UniformDescriptor(program_floor.id, "lightColor");

		floor_mesh.add_uniform(std::move(projection_uniform));
		floor_mesh.add_uniform(std::move(camera_uniform));
		floor_mesh.add_uniform(std::move(light_color_uniform));

		floor_mesh.add_texture(std::move(text_floor));
		Model floor_model;
		floor_model.add_mesh(std::move(floor_mesh));
		floor_model.attach_program(&program_floor);
		app.add_model(std::move(floor_model));

		vector<vector<float>> wall_offsets = {
			{0.0f, 0.0f, 2.5f},
			{0.0f, 0.0f, -2.5f},
			{1.25f, 0.0f, 0.0f},
			{-1.25f, 0.0f, 0.0f}
		};
		vector<pair<float,float>> width_heights = {
			std::make_pair(2.5f, 0.7f),
			std::make_pair(2.5f, 0.7f),
			std::make_pair(5.0f, 0.7f),
			std::make_pair(5.0f, 0.7f)
		};

		for (auto wall_idx = 0; wall_idx < wall_offsets.size(); wall_idx++) {
			Quad wall{
				width_heights[wall_idx].first,
				width_heights[wall_idx].second,
				wall_offsets[wall_idx].data(),
				wall_offsets[wall_idx].data(),
				ScaleFactor{2.0f,1.0f}
			};

			AttributesDescriptor wall_attr {
				2,
				{3, 2},
				{GL_FLOAT, GL_FLOAT, GL_FLOAT},
				{0, 3},
				{5, 5},
			};
			Mesh wall_mesh(&wall.vertices, &wall.indices, &wall_attr);

			TextureDescriptor text_wall(program_floor.id, "texture1", "res/textures/brick_wall.jpg", GL_RGB);

			projection_uniform = UniformDescriptor(program_floor.id, "projection");
			camera_uniform = UniformDescriptor(program_floor.id, "look_at");
			light_color_uniform = UniformDescriptor(program_floor.id, "lightColor");

			wall_mesh.add_uniform(std::move(projection_uniform));
			wall_mesh.add_uniform(std::move(camera_uniform));
			wall_mesh.add_uniform(std::move(light_color_uniform));

			wall_mesh.add_texture(std::move(text_wall));
			Model wall_model;
			wall_model.add_mesh(std::move(wall_mesh));
			wall_model.attach_program(&program_floor);
			app.add_model(std::move(wall_model));
		}

		float ceiling_center_offset[3] = {0.0f, 0.7f, 0.0f};
		float ceiling_center[3] = {0.0f, 0.0f, 0.0f};
		ScaleFactor ceiling_scale_factor{10.0, 10.0};
		Quad ceiling{10.0f, 0.0f, ceiling_center_offset, ceiling_center, ceiling_scale_factor};
		AttributesDescriptor ceiling_attr {
			2,
			{3, 2},
			{GL_FLOAT, GL_FLOAT, GL_FLOAT},
			{0, 3},
			{5, 5},
		};
		Mesh ceiling_mesh(&ceiling.vertices, &ceiling.indices, &ceiling_attr);

		TextureDescriptor text_ceiling(program_floor.id, "texture1", "res/textures/ceiling.jpg", GL_RGB);

		projection_uniform = UniformDescriptor(program_floor.id, "projection");
		camera_uniform = UniformDescriptor(program_floor.id, "look_at");
		light_color_uniform = UniformDescriptor(program_floor.id, "lightColor");

		ceiling_mesh.add_uniform(std::move(projection_uniform));
		ceiling_mesh.add_uniform(std::move(camera_uniform));
		ceiling_mesh.add_uniform(std::move(light_color_uniform));

		ceiling_mesh.add_texture(std::move(text_ceiling));
		Model ceiling_model;
		ceiling_model.add_mesh(std::move(ceiling_mesh));
		ceiling_model.attach_program(&program_floor);
		app.add_model(std::move(ceiling_model));

		// Light cube
		Shader vert_shader_light_cube("src/shaders/light_cube.vert", GL_VERTEX_SHADER);
		Shader frag_shader_light_cube("src/shaders/light_cube.frag", GL_FRAGMENT_SHADER);

		Program program_light_cube;

		program_light_cube.add_shader(&vert_shader_light_cube);
		program_light_cube.add_shader(&frag_shader_light_cube);
		ret = program_light_cube.link_shaders();
		if (ret < 0) {
			cerr<<"There was a problem linking the light cube shaders!"<<endl;
			return -1;
		}

		float light_cube_center[3] = {0.0f, 0.65f, 0.0f};
		Cube light_cube(0.05, light_cube_center);
		AttributesDescriptor light_cube_attr {
			2,
			{3,2},
			{GL_FLOAT, GL_FLOAT, GL_FLOAT},
			{0, 3},
			{5, 5},
		};
		Mesh light_cube_mesh(&light_cube.vertices, &light_cube.indices, &light_cube_attr);

		rotate_about_x_uniform = UniformDescriptor(program_light_cube.id, "rotate_about_x");
		rotate_about_y_uniform = UniformDescriptor(program_light_cube.id, "rotate_about_y");
		rotate_about_z_uniform = UniformDescriptor(program_light_cube.id, "rotate_about_z");

		translate_uniform = UniformDescriptor(program_light_cube.id, "translate");
		projection_uniform = UniformDescriptor(program_light_cube.id, "projection");
		camera_uniform = UniformDescriptor(program_light_cube.id, "look_at");

		light_cube_mesh.add_uniform(std::move(rotate_about_x_uniform));
		light_cube_mesh.add_uniform(std::move(rotate_about_y_uniform));
		light_cube_mesh.add_uniform(std::move(rotate_about_z_uniform));
		light_cube_mesh.add_uniform(std::move(translate_uniform));
		light_cube_mesh.add_uniform(std::move(projection_uniform));
		light_cube_mesh.add_uniform(std::move(camera_uniform));

		Model light_cube_model;
		light_cube_model.add_mesh(std::move(light_cube_mesh));
		light_cube_model.attach_program(&program_light_cube);

		app.add_model(std::move(light_cube_model));

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

		app.attach_text_manager(std::move(text_manager));

		app.render_models();
	} catch (std::exception &e) {
		std::cerr<<"Application error! "<<e.what()<<std::endl;
		return -1;
	}

	return 0;
}
