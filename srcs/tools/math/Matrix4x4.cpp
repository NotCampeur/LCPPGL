/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix4x4.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:36:41 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/27 15:32:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Matrix4x4.hpp"
#include "lcppgl_tools.hpp"

using namespace lcppgl::tools;

Matrix4x4::Matrix4x4()
: matrix()
{
	float (*m)[4] = matrix;

	m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
	m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0;
	m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
}

Matrix4x4::Matrix4x4(const Matrix4x4 &to_copy)
: matrix()
{
	for (int i(0); i < 4; ++i)
		for (int j(0); j < 4; ++j)
			matrix[i][j] = to_copy.matrix[i][j];
}

Matrix4x4 &
Matrix4x4::operator = (const Matrix4x4 & to_assign)
{
	if (this != &to_assign)
	{
		for (int i(0); i < 4; ++i)
			for (int j(0); j < 4; ++j)
				matrix[i][j] = to_assign.matrix[i][j];
	}
	return *this;
}

Matrix4x4::~Matrix4x4()
{}

Matrix4x4
Matrix4x4::x_rotation(const float ax) const
{
	Matrix4x4 res;

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

Matrix4x4
Matrix4x4::y_rotation(const float ay) const
{
	Matrix4x4 res;

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

Matrix4x4
Matrix4x4::z_rotation(const float az) const
{
	Matrix4x4 res;

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

void
Matrix4x4::set_to_rotate(const float x, const float y, const float z)
{
	Matrix4x4 x_rot(x_rotation(x));
	Matrix4x4 y_rot(y_rotation(y));
	Matrix4x4 z_rot(z_rotation(z));

	*this = x_rot * y_rot * z_rot;
}

void
Matrix4x4::set_to_translate(const float dx, const float dy, const float dz)
{
	float (*m)[4] = matrix;

	m[0][0] = 1.0f;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
	m[1][0] = 0.0f;	m[1][1] = 1.0f;	m[1][2] = 0.0f;	m[1][3] = 0;
	m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = 1.0f;	m[2][3] = 0;
	m[3][0] = dx;	m[3][1] = dy;	m[3][2] = dz;	m[3][3] = 1;
}

void
Matrix4x4::set_to_scale(const float dx, const float dy, const float dz)
{
	float (*m)[4] = matrix;

	m[0][0] = dx;	m[0][1] = 0.0f;	m[0][2] = 0.0f;	m[0][3] = 0;
	m[1][0] = 0.0f;	m[1][1] = dy;	m[1][2] = 0.0f;	m[1][3] = 0;
	m[2][0] = 0.0f;	m[2][1] = 0.0f;	m[2][2] = dz;	m[2][3] = 0;
	m[3][0] = 0.0f;	m[3][1] = 0.0f;	m[3][2] = 0.0f;	m[3][3] = 1;
}

Matrix4x4
Matrix4x4::look_at(const Vector3 &cam_pos, const Vector3 &cam_target,
					const Vector3 &up_point)
{
	Matrix4x4 view;
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

Matrix4x4
Matrix4x4::perspective(float fov, float ratio, float z_far, float z_near)
{
	Matrix4x4 projection;

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

Matrix4x4
Matrix4x4::operator * (const Matrix4x4 &m) const
{
	Matrix4x4 res;

	for (int i(0); i < 4; ++i)
		for (int j(0); j < 4; ++j)
			res.matrix[i][j] = (  matrix[i][0] * m.matrix[0][j]
								+ matrix[i][1] * m.matrix[1][j]
								+ matrix[i][2] * m.matrix[2][j]
								+ matrix[i][3] * m.matrix[3][j]);
	return res;
}

Vector3
Matrix4x4::operator * (const Vector3 & v) const
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

std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Matrix4x4 &matrix)
{
	for (int i(0); i < 4; ++i)
	{
		for (int j(0); j < 4; ++j)
			os << matrix.matrix[i][j] << ' ';
		os << '\n';
	}
	return os;
}