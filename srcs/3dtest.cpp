#include "lcppgl.hpp"
#include <vector>
#include <cstdlib>
#include "Fps_counter.hpp"

using namespace lcppgl::tools;

void	draw_cube(lcppgl::Context &context, void *param)
{
	key_pressed * keys(reinterpret_cast<key_pressed *>(param));

	static Fps_counter fps;
	static lcppgl::ZPrinter zprinter(context, lcppgl::Camera(Vector3(0, 0, 5.0f)));
	static lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
	static std::vector<Mesh> meshes;
	
	context.set_fps_limit(0);

	if (meshes.size() == 0)
	{
		Mesh cube = Mesh::get_from_file("./ressources/cube.obj");
		meshes.push_back(cube);
		cube.pos = Vector3(-6.1f, 3, 0);
		meshes.push_back(cube);
		cube.pos = Vector3(-6.1f, -2.5f, 0);
		meshes.push_back(cube);
		cube.pos = Vector3(6.1f, -2.5f, 0);
		meshes.push_back(cube);
		cube.pos = Vector3(6.1f, 3, 0);
		meshes.push_back(cube);
	}

	fps.update();

	zprinter.clear();
	writer.put_text(std::to_string(fps.get()), Rectangle(3, 3, 25, 20), Color(255, 255, 255, 255));
	zprinter.put_meshes(meshes.data(), meshes.size());
	zprinter.present();

	if (keys != NULL)
	{
		for(Mesh & m: meshes)
		{
			if (keys->up)
				m.pos.y += 0.1f;
			if (keys->down)
				m.pos.y -= 0.1f;
			if (keys->left)
				m.pos.x -= 0.1f;
			if (keys->right)
				m.pos.x += 0.1f;
			if (keys->plus)
				m.pos.z += 0.1f;
			if (keys->minus)
				m.pos.z -= 0.1f;
			if (keys->d)
				m.rotation.y += 1.0f;
			if (keys->a)
				m.rotation.y -= 1.0f;
			if (keys->s)
				m.rotation.x += 1.0f;
			if (keys->w)
				m.rotation.x -= 1.0f;
			if (keys->q)
				m.rotation.z += 1.0f;
			if (keys->e)
				m.rotation.z -= 1.0f;
			if (keys->space)
				std::cout << m << std::endl;
		}
		keys->reset();
	}
}