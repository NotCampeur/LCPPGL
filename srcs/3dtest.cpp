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

struct Mesh
{
	std::string				name;
	std::vector<Vector3>	vertices;
	std::vector<Face>		faces;
	Vector3					pos;
	Vector3					rotation;

	Mesh(std::string _name, int vertices_count, int faces_count)
	: name(_name), vertices(vertices_count)
	, faces(faces_count)
	{}

	Mesh(const Mesh & to_copy)
	: name(to_copy.name + "_copy")
	, vertices(to_copy.vertices.size())
	, faces(to_copy.faces.size())
	, pos(to_copy.pos), rotation(to_copy.rotation)
	{
		vertices = to_copy.vertices;
		faces = to_copy.faces;
	}

	Mesh &operator = (const Mesh & to_assign)
	{
		if (this != &to_assign)
		{
			name = to_assign.name + "_copy";
			vertices = to_assign.vertices;
			faces = to_assign.faces;
			pos = to_assign.pos;
			rotation = to_assign.rotation;
		}
		return *this;
	}

	~Mesh()
	{
	}
};

std::ostream & operator << (std::ostream & os, const Mesh & to_print)
{
	os << to_print.name << " has " << to_print.vertices.size() << " vertices :\n";
	for (size_t i(0); i < to_print.vertices.size(); ++i)
		os << i << " : " << to_print.vertices[i] << '\n';
	os << to_print.name << " has " << to_print.faces.size() << " faces :\n";
	for (size_t i(0); i < to_print.faces.size(); ++i)
		os << i << " : " << to_print.faces[i] << '\n';
	os << to_print.name << " position is : " << to_print.pos << "\n"
		 << to_print.name << " rotation is : " << to_print.pos;

	return os;
}

/**
 * @brief A 4 by 4 matrix.
 */
struct Matrix
{
	float	matrix[4][4];

	Matrix()
	: matrix()
	{
		float (*m)[4] = matrix;

		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0;
		m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	}

	Matrix(const Matrix &to_copy)
	: matrix()
	{
		for (int i(0); i < 4; ++i)
			for (int j(0); j < 4; ++j)
				matrix[i][j] = to_copy.matrix[i][j];
	}

	Matrix &operator = (const Matrix & to_assign)
	{
		if (this != &to_assign)
		{
			for (int i(0); i < 4; ++i)
				for (int j(0); j < 4; ++j)
					matrix[i][j] = to_assign.matrix[i][j];
		}
		return *this;
	}

	~Matrix()
	{}

	Matrix	x_rotation(const float ax) const
	{
		Matrix res;

		float ra = to_radian(ax);
		float cosra = cosf(ra);
		float sinra = sinf(ra);
		float (*m)[4] = res.matrix;

		m[0][0] = 1.0f;	m[0][1] = 0.0f;		m[0][2] = 0.0f;		m[0][3] = 0;
		m[1][0] = 0.0f;	m[1][1] = cosra;	m[1][2] = sinra;	m[1][3] = 0;
		m[2][0] = 0.0f;	m[2][1] = -sinra;	m[2][2] = cosra;	m[2][3] = 0;
		m[3][0] = 0;	m[3][1] = 0;		m[3][2] = 0;		m[3][3] = 1;

		return res;
	}

	Matrix	y_rotation(const float ay) const
	{
		Matrix res;

		float ra = to_radian(ay);
		float cosra = cosf(ra);
		float sinra = sinf(ra);
		float (*m)[4] = res.matrix;

		m[0][0] = cosra;	m[0][1] = 0.0f;	m[0][2] = -sinra;	m[0][3] = 0;
		m[1][0] = 0.0f;		m[1][1] = 1.0f;	m[1][2] = 0.0f;		m[1][3] = 0;
		m[2][0] = sinra;	m[2][1] = 0.0f;	m[2][2] = cosra;	m[2][3] = 0;
		m[3][0] = 0;		m[3][1] = 0;	m[3][2] = 0;		m[3][3] = 1;

		return res;
	}

	Matrix	z_rotation(const float az) const
	{
		Matrix res;

		float ra = to_radian(az);
		float cosra = cosf(ra);
		float sinra = sinf(ra);
		float (*m)[4] = res.matrix;

		m[0][0] = cosra;	m[0][1] = sinra;	m[0][2] = 0.0f;	m[0][3] = 0;
		m[1][0] = -sinra;	m[1][1] = cosra;	m[1][2] = 0.0f;	m[1][3] = 0;
		m[2][0] = 0.0f;		m[2][1] = 0.0f;		m[2][2] = 1.0f;	m[2][3] = 0;
		m[3][0] = 0;		m[3][1] = 0;		m[3][2] = 0;	m[3][3] = 1;

		return res;
	}

	void	set_to_rotate(const float x, const float y, const float z)
	{
		Matrix x_rot(x_rotation(x));
		Matrix y_rot(y_rotation(y));
		Matrix z_rot(z_rotation(z));

		*this = x_rot * y_rot * z_rot;
	}

	void	set_to_translate(const float dx, const float dy, const float dz)
	{
		float (*m)[4] = matrix;

		m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
		m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0;
		m[3][0] = dx;	m[3][1] = dy;	m[3][2] = dz;	m[3][3] = 1;
	}

	void	set_to_scale(const float dx, const float dy, const float dz)
	{
		float (*m)[4] = matrix;

		m[0][0] = dx;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
		m[1][0] = 0.0f;	m[1][1] = dy;	m[1][2] = 0.0f;	m[1][3] = 0;
		m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = dz;	m[2][3] = 0;
		m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1;
	}

	/**
	 * @brief Set the matrix to perform view transformation (right handed)
	 * 
	 * @param cam_pos The Camera.pos vector3 telling where the camera is.
	 * 					Used for translation.
	 * @param cam_target The Camera.target vector3 telling where the camera look at.
	 * @param up_point Usually [0, 1, 0], tells where is the up of the world.
	 */
	static Matrix	look_at(const Vector3 &cam_pos, const Vector3 &cam_target,
						const Vector3 &up_point)
	{
		Matrix view;
		Vector3 z_axis;
		Vector3 x_axis;
		Vector3 y_axis;

		// Right handed
		z_axis = Vector3((cam_pos - cam_target).normalize());
		
		x_axis = Vector3((up_point.cross(z_axis)).normalize());
		y_axis = Vector3(z_axis.cross(x_axis));

		float (*m)[4] = view.matrix;

		m[0][0] = x_axis.x;	m[0][1] = y_axis.x;	m[0][2] = z_axis.x;	m[0][3] = 0.0f;
		m[1][0] = x_axis.y;	m[1][1] = y_axis.y;	m[1][2] = z_axis.y;	m[1][3] = 0.0f;
		m[2][0] = x_axis.z;	m[2][1] = y_axis.z;	m[2][2] = z_axis.z;	m[2][3] = 0.0f;
		m[3][0] = -x_axis.dot(cam_pos);	m[3][1] = -y_axis.dot(cam_pos);	m[3][2] = -z_axis.dot(cam_pos);	m[3][3] = 1.0f;

		return view;
	}

	static Matrix perspective(float fov, float ratio, float z_far, float z_near)
	{
		Matrix projection;

		float horizontal_scale;
		float vertical_scale;
		float z_axis_adjusment;
		float tan_tmp(tanf(fov));

		horizontal_scale = vertical_scale = 1.0f / tan_tmp;
		horizontal_scale /= ratio;
		z_axis_adjusment = z_far / (z_far - z_near);

		projection.matrix[0][0] = horizontal_scale;
		projection.matrix[1][1] = vertical_scale;

		projection.matrix[2][2] = -z_axis_adjusment; 	// Whether or not an object is between
		projection.matrix[2][3] = -1.0f;	//	 the two planes;

		// if == 0, the projection matrix is not a perspective projection matrix.
		// if < 0 then it's a right handed coordinate system.
		// if > 0 then it's a left handed coordinate system.
		projection.matrix[3][2] = -((z_far * z_near) / (z_far - z_near));

		projection.matrix[3][3] = 0;

		return projection;
	}

	Matrix	operator * (const Matrix &m) const
	{
		Matrix res;

		for (int i(0); i < 4; ++i)
			for (int j(0); j < 4; ++j)
				res.matrix[i][j] = (  matrix[i][0] * m.matrix[0][j]
									+ matrix[i][1] * m.matrix[1][j]
									+ matrix[i][2] * m.matrix[2][j]
									+ matrix[i][3] * m.matrix[3][j]);
		return res;
	}

	Vector3 operator * (const Vector3 & v) const
	{
		const float (*m)[4] = matrix;

		Vector3 res(
			v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0],
			v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1],
			v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2]
		);
		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

		if (w != 1)
		{
			res.x /= w;
			res.y /= w;
			res.z /= w;
		}
		return res;
	}
};

std::ostream &operator<<(std::ostream & os, const Matrix &matrix)
{
	for (int i(0); i < 4; ++i)
	{
		for (int j(0); j < 4; ++j)
			os << matrix.matrix[i][j] << ' ';
		os << '\n';
	}
	return os;
}

// Transform a 3D point into a 2D point using the given matrix.
// The returned vector3 only have a x and y data.
Vector3	project(const lcppgl::Context &context,
				const Vector3 &vertex, const Matrix &matrix)
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
	Matrix	view(Matrix::look_at(cam.pos, cam.target, Vector3(0, 1, 0)));

	// std::cout << "View matrix :\n" << view << '\n';

	//2 = Projection matrix applying FOV;
	Matrix	projection(Matrix::perspective(0.7854f,
		static_cast<float>(context.width()) / static_cast<float>(context.height()),
		1.0f, 0.01f));

	// std::cout << "projection matrix :\n" << projection << '\n';
	zprinter.clear();

	for (int i(0); i < mesh_nb; ++i)
	{
		//3 world matrix on each mesh
		Matrix	world;
		Matrix	rotation;
		Matrix	translation;

		rotation.set_to_rotate(mesh[i].rotation.x, mesh[i].rotation.y, mesh[i].rotation.z);
		translation.set_to_translate(mesh[i].pos.x, mesh[i].pos.y, mesh[i].pos.z);

		// std::cout << "rotation matrix :\n" << rotation << '\n';
		// std::cout << "translation matrix :\n" << translation << '\n';

		world = rotation * translation;
		// std::cout << "world matrix :\n" << world << '\n';

		//4 the final transform matrix :
		Matrix transform;
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