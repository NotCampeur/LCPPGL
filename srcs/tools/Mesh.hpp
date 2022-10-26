/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:12:12 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:28:23 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_MESH_HPP
# define LCPPGL_MESH_HPP

# include <iostream>
# include <vector>
# include "Vector3.hpp"
# include "Face.hpp"

namespace lcppgl
{
	namespace tools
	{
		struct Mesh
		{
			std::string				name;
			std::vector<Vector3>	vertices;
			std::vector<Face>		faces;
			Vector3					pos;
			Vector3					rotation;

			Mesh(std::string _name, int vertices_count, int faces_count);

			Mesh(const Mesh & to_copy);

			Mesh &operator = (const Mesh & to_assign);

			~Mesh();
		};
	}
}

std::ostream & operator << (std::ostream & os, const lcppgl::tools::Mesh & to_print);

#endif