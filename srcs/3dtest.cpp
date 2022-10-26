#include "lcppgl.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace lcppgl::tools;

// Might return SDL_Point[] later.
void	scan_line(lcppgl::ZPrinter &zprinter, Color color,
					float y,
					const Vector3 & a, const Vector3 & b,
					const Vector3 & c, const Vector3 & d)
{
	float gradient1 = (a.y != b.y) ? (y - a.y) / (b.y - a.y) : 1.0f;
	float gradient2 = (c.y != d.y) ? (y - c.y) / (d.y - c.y) : 1.0f;

	float start_x(interpolate(a.x, b.x, gradient1));
	float end_x(interpolate(c.x, d.x, gradient2));

	float z1 = interpolate(a.z, b.z, gradient1);
	float z2 = interpolate(c.z, d.z, gradient2);

	for (float x(start_x); x < end_x; ++x)
	{
		float z_gradient = (x - start_x) / (end_x - start_x);
		float current_z = interpolate(z1, z2, z_gradient);
		zprinter.put_pixel(x, y, current_z, color);
	}
}

void	rasterize(lcppgl::ZPrinter &zprinter,
					Vector3 a, Vector3 b, Vector3 c,
					Color color)
{
	float a_b_slope(0.0f);
	float a_c_slope(0.0f);

	// Sort vertices based on their y position.
	if (a.y > b.y)
		std::swap(a, b);
	if (b.y > c.y)
		std::swap(b, c);
	if (a.y > b.y)
		std::swap(a, b);

	if (b.y - a.y > 0)
		a_b_slope = (b.x - a.x) / (b.y - a.y);
	if (c.y - a.y > 0)
		a_c_slope = (c.x - a.x) / (c.y - a.y);
	
	if (a_b_slope > a_c_slope)
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				scan_line(zprinter, color, y, a, c, a, b);
			else
				scan_line(zprinter, color, y, a, c, b, c);
	}
	else
	{
		for (float y(a.y); y < c.y; ++y)
			if (y < b.y)
				scan_line(zprinter, color, y, a, b, a, c);
			else
				scan_line(zprinter, color, y, b, c, a, c);
	}
}

// Transform a 3D point into a 2D point using the given matrix.
// The returned vector3 only have a x and y data.
Vector3	project(const lcppgl::Context &context,
				const Vector3 &vertex, const Matrix4x4 &matrix)
{
	Vector3 td_point = matrix * vertex;

	// std::cout << "Mid projection 2DPoint : " << td_point << '\n';

	td_point.x = (td_point.x + 1) * 0.5 * context.width();
	td_point.y = (1 - (td_point.y + 1) * 0.5) * context.height();
	
	// std::cout << "From : " << vertex << " to : " << td_point << '\n';
	return td_point;
}

void	render(lcppgl::Context &context, lcppgl::Camera &cam, Mesh mesh[], int mesh_nb)//List of mesh in futur
{
	lcppgl::ZPrinter zprinter(context);

	//1 = View matrix
	Matrix4x4	view(Matrix4x4::look_at(cam.pos, cam.target, Vector3(0, 1, 0)));

	// std::cout << "View matrix :\n" << view << '\n';

	//2 = Projection matrix applying FOV;
	Matrix4x4	projection(Matrix4x4::perspective(0.7854f,
		static_cast<float>(context.width()) / static_cast<float>(context.height()),
		1.0f, 0.01f));

	// std::cout << "projection matrix :\n" << projection << '\n';
	zprinter.clear();

	for (int i(0); i < mesh_nb; ++i)
	{
		//3 world matrix on each mesh
		Matrix4x4	world;
		Matrix4x4	rotation;
		Matrix4x4	translation;

		rotation.set_to_rotate(mesh[i].rotation.x, mesh[i].rotation.y, mesh[i].rotation.z);
		translation.set_to_translate(mesh[i].pos.x, mesh[i].pos.y, mesh[i].pos.z);

		// std::cout << "rotation matrix :\n" << rotation << '\n';
		// std::cout << "translation matrix :\n" << translation << '\n';

		world = rotation * translation;
		// std::cout << "world matrix :\n" << world << '\n';

		//4 the final transform matrix :
		Matrix4x4 transform;
		transform = world * view * projection;
		
		//5 For each faces :
		// std::cout << "Transform matrix :\n" << transform << '\n';
		for (size_t f(0); f < mesh[i].faces.size(); ++f)
		{
			Color white(f % 255, f % 255, f % 255, 255);
			Vector3 vertex_a = mesh[i].vertices[mesh[i].faces[f].a];
			Vector3 vertex_b = mesh[i].vertices[mesh[i].faces[f].b];
			Vector3 vertex_c = mesh[i].vertices[mesh[i].faces[f].c];

			Vector3 pixel_a = project(context, vertex_a, transform);
			Vector3 pixel_b = project(context, vertex_b, transform);
			Vector3 pixel_c = project(context, vertex_c, transform);
			//6 Draw of 2DVertex;
			// zprinter.put_triangle(pixel_a.x, pixel_a.y, pixel_b.x, pixel_b.y,
			// 					pixel_c.x, pixel_c.y, white);
			rasterize(zprinter, pixel_a, pixel_b, pixel_c, white);
		}
	}

	// std::cout << "\n\n";
	zprinter.present();
}

Mesh	get_mesh(const std::string &path_to_file)
{
	Mesh result("mesh", 0, 0);
	std::ifstream file(path_to_file);

	if (file.fail())
	{
		std::cerr << "Cannot open `" << path_to_file << "`\n";
	}
	while (file.good())
	{
		char buffer[50] = {};

		file.getline(buffer, 50, '\n');
		if (buffer[0] == '#')
			continue;
		else if (buffer[0] == 'o')
			result.name = std::string(buffer + 2);
		else if (buffer[0] == 'v')
		{
			Vector3	vertex;
			char 	*y_val;
			char 	*z_val;

			vertex.x = strtof(buffer + 2, &y_val);
			vertex.y = strtof(y_val, &z_val);
			vertex.z = strtof(z_val, NULL);

			result.vertices.push_back(vertex);
		}
		else if (buffer[0] == 'f')
		{
			Face	face;
			char 	*b_val;
			char 	*c_val;

			// Need to remove one because faces in object files start at 1 and not 0
			face.a = strtol(buffer + 2, &b_val, 10) - 1;
			face.b = strtol(b_val, &c_val, 10) - 1;
			face.c = strtol(c_val, NULL, 10) - 1;

			result.faces.push_back(face);
		}
	}
	file.close();
	return result;
}

void	draw_cube(lcppgl::Context &context)
{
	static lcppgl::Camera cam;

	if (cam.pos.z == 0.0f)
	{
		cam.pos = Vector3(0, 0, 5.0f);
		cam.target = Vector3(0, 0, 0.0f);
	}
	static Mesh suzanne = get_mesh("./ressources/suzanne.obj");

	Mesh meshes[1] = {suzanne};

	context.set_fps_limit(0);
	
	render(context, cam, meshes, 1);

	// suzanne.rotation.x += 1.0f;
	suzanne.rotation.y += 1.0f;
	// suzanne.rotation.z += 1.0f;
}