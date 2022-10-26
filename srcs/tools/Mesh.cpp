/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:25:11 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:28:48 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"

using namespace lcppgl::tools;

Mesh::Mesh(std::string _name, int vertices_count, int faces_count)
: name(_name), vertices(vertices_count), faces(faces_count)
{}

Mesh::Mesh(const Mesh & to_copy)
: name(to_copy.name + "_copy")
, vertices(to_copy.vertices.size())
, faces(to_copy.faces.size())
, pos(to_copy.pos), rotation(to_copy.rotation)
{
	vertices = to_copy.vertices;
	faces = to_copy.faces;
}

Mesh &
Mesh::operator = (const Mesh & to_assign)
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

Mesh::~Mesh()
{}

std::ostream & operator << (std::ostream & os, const lcppgl::tools::Mesh & to_print)
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