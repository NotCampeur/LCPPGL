#include "lcppgl.hpp"
#include <vector>
#include <cstdlib>
#include "Fps_counter.hpp"

using namespace lcppgl::tools;

void	draw_cube(lcppgl::Context &context, void *param)
{
	bool slow(false);
	if (param != NULL)
		slow = *reinterpret_cast<bool *>(param);
	static Fps_counter fps;
	static lcppgl::ZPrinter zprinter(context, lcppgl::Camera(Vector3(0, 0, 2.0f)));
	// static lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
	static std::vector<Mesh> meshes;
	
	context.set_fps_limit((slow == true) ? 1 : 0);

	if (meshes.size() == 0)
		meshes.push_back(Mesh::get_from_file("./ressources/suzanne.obj"));

	fps.update();

	zprinter.clear();
	// writer.put_text(std::to_string(fps.get()), Rectangle(3, 3, 25, 20), Color(255, 255, 255, 255));
	zprinter.put_meshes(meshes.data(), meshes.size());
	zprinter.present();

	for(Mesh & m: meshes)
		m.rotation.y += 1.0f;
}