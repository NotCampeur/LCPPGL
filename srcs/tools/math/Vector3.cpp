/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:39:43 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 17:21:34 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector3.hpp"

using namespace lcppgl::tools;

Vector3::Vector3(float _x, float _y, float _z)
: x(_x), y(_y), z(_z)
{}

Vector3::Vector3(const Vector3 &to_copy)
: x(to_copy.x), y(to_copy.y), z(to_copy.z)
{}

Vector3 &
Vector3::operator=(const Vector3 &to_assign)
{
	if (this != &to_assign)
	{
		x = to_assign.x;
		y = to_assign.y;
		z = to_assign.z;
	}
	return *this;
}

Vector3::~Vector3() {}

Vector3
Vector3::operator + (const Vector3 &vec) const
{
	return (Vector3(x + vec.x, y + vec.y, z + vec.z));
}

Vector3
Vector3::operator - (const Vector3 &vec) const
{
	return (Vector3(x - vec.x, y - vec.y, z - vec.z));
}

Vector3
Vector3::operator * (const Vector3 &vec) const
{
	return (Vector3(x * vec.x, y * vec.y, z * vec.z));
}

Vector3
Vector3::operator / (const Vector3 &vec) const
{
	return (Vector3(x / vec.x, y / vec.y, z / vec.z));
}

Vector3
Vector3::normalize() const
{
	float length(std::sqrt((x * x) + (y * y) + (z * z)));

	return (Vector3(x / length, y / length, z / length));
}

float
Vector3::dot(const Vector3 &vec) const
{
	return (x * vec.x + y * vec.y + z * vec.z);
}

Vector3
Vector3::cross(const Vector3 &vec) const
{
	return (Vector3(
		y * vec.z - z * vec.y,
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x
	));
}

std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Vector3 &pos)
{
	os << "[" << pos.x << ',' << pos.y << ',' << pos.z << ']';
	return os;
}