/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Face.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:12:12 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:18:26 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_FACE_HPP
# define LCPPGL_FACE_HPP

# include <iostream>

namespace lcppgl
{
	namespace tools
	{
		/**
		 * @brief Struct designed to keep vertices index in Mesh.
		 * Only store triangles.
		 */
		struct Face
		{
			int a;
			int b;
			int c;

			Face(int _a = 0, int _b = 0, int _c = 0);

			Face(const Face & to_copy);

			Face & operator = (const Face & to_assign);

			~Face();
		};

	}
}
std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Face &face);

#endif