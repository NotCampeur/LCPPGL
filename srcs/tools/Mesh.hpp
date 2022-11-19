/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:12:12 by ldutriez          #+#    #+#             */
/*   Updated: 2022/11/03 14:37:57 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_MESH_HPP
# define LCPPGL_MESH_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include "Vector3.hpp"
# include "Face.hpp"

namespace lcppgl
{
	namespace tools
	{
		struct Vertex
		{
			Vector3 normal;
			Vector3 coordinates;
			Vector3 world_coordinates;

			Vertex(const Vector3 &p_normal = Vector3(), const Vector3 &p_coordinates = Vector3(),
					const Vector3 &p_world_coordinates = Vector3())
			: normal(p_normal), coordinates(p_coordinates)
			, world_coordinates(p_world_coordinates)
			{}
		};

		struct Mesh
		{
			std::string				name;
			std::vector<Vertex>		vertices;
			// std::vector<Vector3>	vertices;
			std::vector<Face>		faces;
			Vector3					pos;
			Vector3					rotation;

			Mesh(std::string _name, int vertices_count, int faces_count);

			Mesh(const Mesh & to_copy);

			Mesh &operator = (const Mesh & to_assign);

			~Mesh();

			static Mesh get_from_file(const std::string & path_to_file);
		};
	}
}

std::ostream & operator << (std::ostream & os, const lcppgl::tools::Mesh & to_print);

#endif