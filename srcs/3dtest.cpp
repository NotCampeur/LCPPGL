#include "lcppgl.hpp"
#include <cmath>

float	to_radian(int degree)
{
	return (static_cast<float>(degree * (M_PI / 180)));
}

struct Vector3
{
	float	x;
	float	y;
	float	z;
	float	w;

	Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f): x(_x), y(_y), z(_z), w(_w)
	{}

	Vector3(const Vector3 &to_copy)
	: x(to_copy.x), y(to_copy.y), z(to_copy.z), w(to_copy.w)
	{}

	Vector3 &operator=(const Vector3 &to_assign)
	{
		if (this != &to_assign)
		{
			x = to_assign.x;
			y = to_assign.y;
			z = to_assign.z;
			w = to_assign.w;
		}
		return *this;
	}

	~Vector3() {}

	Vector3 operator + (const Vector3 &vec) const
	{
		return (Vector3(x + vec.x, y + vec.y, z + vec.z));
	}

	Vector3 operator - (const Vector3 &vec) const
	{
		return (Vector3(x - vec.x, y - vec.y, z - vec.z));
	}

	Vector3 operator * (const Vector3 &vec) const
	{
		return (Vector3(x * vec.x, y * vec.y, z * vec.z));
	}

	Vector3 operator / (const Vector3 &vec) const
	{
		return (Vector3(x / vec.x, y / vec.y, z / vec.z));
	}

	Vector3	normalize()
	{
		float length(std::sqrt((x * x) + (y * y) + (z * z)));

		return (Vector3(x / length, y / length, z / length));
	}

	float dot(const Vector3 &vec) const
	{
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	Vector3	cross(const Vector3 &vec) const
	{
		return (Vector3(
			y * vec.z - z * vec.y,
			z * vec.x - x * vec.z,
			x * vec.y - y * vec.x
		));
	}
};


std::ostream &operator<<(std::ostream & os, const Vector3 &pos)
{
	os << "[" << pos.x << ',' << pos.y << ',' << pos.z << ',' << pos.w << ']';
	return os;
}

struct Camera
{
	Vector3	pos;
	Vector3	target;
};

struct Mesh
{
	std::string name;
	Vector3		*vertices;
	int			vertices_nb;
	Vector3		pos;
	Vector3		rotation;

	Mesh(std::string _name, int vertices_count)
	: name(_name), vertices(new Vector3[vertices_count]), vertices_nb(vertices_count)
	{}

	~Mesh()
	{
		delete[] vertices;
	}
};

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

void	render(lcppgl::Context &context, Camera &cam, Mesh &mesh)//List of mesh in futur
{
	lcppgl::Printer printer(context);

	//1 = View matrix
	Matrix	view(Matrix::look_at(cam.pos, cam.target, Vector3(0, 1, 0)));

	// std::cout << "View matrix :\n" << view << '\n';

	//2 = Projection matrix applying FOV;
	Matrix	projection(Matrix::perspective(0.7854f,
		static_cast<float>(context.width()) / static_cast<float>(context.height()),
		1.0f, 0.01f));

	// std::cout << "projection matrix :\n" << projection << '\n';

	//3 world matrix on each mesh
	Matrix	world;
	Matrix rotation;
	Matrix translation;

	rotation.set_to_rotate(mesh.rotation.x, mesh.rotation.y, mesh.rotation.z);
	translation.set_to_translate(mesh.pos.x, mesh.pos.y, mesh.pos.z);

	// std::cout << "rotation matrix :\n" << rotation << '\n';
	// std::cout << "translation matrix :\n" << translation << '\n';

	world = rotation * translation;
	// std::cout << "world matrix :\n" << world << '\n';

	//4 the final transform matrix :
	Matrix transform;
	transform = world * view * projection;
	
	printer.clear();

	//5 For each vertices :
	// std::cout << "Transform matrix :\n" << transform << '\n';
	for (int i(0); i < mesh.vertices_nb; ++i)
	{
		lcppgl::tools::Color color;
		if (i % 2 == 0)
			color = lcppgl::tools::Color(0, i * 28 + 58, 0, 255);
		else if (i % 3 == 0)
			color = lcppgl::tools::Color(i * 28 + 58, 0, 0, 255);
		else
			color = lcppgl::tools::Color(0, 0, i * 28 + 58, 255);
		Vector3 td_vertex = project(context, mesh.vertices[i], transform);
		//6 Draw of 2DVertex;
		printer.put_filled_rect(lcppgl::tools::Rectangle(td_vertex.x, td_vertex.y, 10, 10), color);
	}

	// std::cout << "\n\n";
	printer.present();
}

void	draw_cube(lcppgl::Context &context)
{
	static Camera cam;

	if (cam.pos.z == 0.0f)
	{
		cam.pos = Vector3(0, 0, 10.0f);
		cam.target = Vector3(0, 0, 0.0f);
	}

	static Mesh	cube = Mesh("Cube", 8);

	if (cube.pos.x == 0.0f)
	{
		cube.pos = Vector3(0, 0, 0.0f);
		cube.vertices[0] = Vector3(-1.0f, 1.0f, 1.0f);
		cube.vertices[1] = Vector3(1.0f, 1.0f, 1.0f);
		cube.vertices[2] = Vector3(-1.0f, -1.0f, 1.0f);
		cube.vertices[3] = Vector3(-1.0f, -1.0f, -1.0f);
		cube.vertices[4] = Vector3(-1.0f, 1.0f, -1.0f);
		cube.vertices[5] = Vector3(1.0f, 1.0f, -1.0f);
		cube.vertices[6] = Vector3(1.0f, -1.0f, 1.0f);
		cube.vertices[7] = Vector3(1.0f, -1.0f, -1.0f);
	}

	context.set_fps_limit(0);
	
	render(context, cam, cube);

	// cube.rotation.x += 1.0f;
	cube.rotation.y += 1.0f;
	// cube.rotation.z += 1.0f;
}