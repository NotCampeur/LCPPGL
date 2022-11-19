/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:25:11 by ldutriez          #+#    #+#             */
/*   Updated: 2022/11/19 18:37:43 by ldutriez         ###   ########.fr       */
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

Mesh
Mesh::get_from_file(const std::string & path_to_file)
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

std::ostream & operator << (std::ostream & os, const lcppgl::tools::Mesh & to_print)
{
	os << to_print.name << " has " << to_print.vertices.size() << " vertices :\n";
	for (size_t i(0); i < to_print.vertices.size(); ++i)
		os << i << " : " << to_print.vertices[i] << '\n';
	os << to_print.name << " has " << to_print.faces.size() << " faces :\n";
	for (size_t i(0); i < to_print.faces.size(); ++i)
		os << i << " : " << to_print.faces[i] << '\n';
	os << to_print.name << " position is : " << to_print.pos << "\n"
		 << to_print.name << " rotation is : " << to_print.rotation;

	return os;
}