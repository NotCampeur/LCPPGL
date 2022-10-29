#include "lcppgl.hpp"
#include <vector>
#include <cstdlib>

using namespace lcppgl::tools;

void	draw_cube(lcppgl::Context &context, void *param)
{
	bool slow(false);
	if (param != NULL)
		slow = *reinterpret_cast<bool *>(param);

	static lcppgl::ZPrinter zprinter(context, lcppgl::Camera(Vector3(0, 0, 5.0f)));
	static std::vector<Mesh> meshes;
	
	context.set_fps_limit((slow == true) ? 1 : 0);

	if (meshes.size() == 0)
		meshes.push_back(Mesh::get_from_file("./ressources/suzanne.obj"));

	zprinter.clear();
	zprinter.put_meshes(meshes.data(), meshes.size());
	zprinter.present();

	for(Mesh & m: meshes)
		m.rotation.y += 1.0f;
}