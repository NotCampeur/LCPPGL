/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:37:04 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 17:19:56 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_VECTOR3_HPP
# define LCPPGL_VECTOR3_HPP

# include <iostream>
# include <cmath>

namespace lcppgl
{
	namespace tools
	{
		struct Vector3
		{
			float	x;
			float	y;
			float	z;

			Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

			Vector3(const Vector3 &to_copy);

			Vector3 &operator=(const Vector3 &to_assign);

			~Vector3();

			Vector3 operator + (const Vector3 &vec) const;
			Vector3 operator - (const Vector3 &vec) const;
			Vector3 operator * (const Vector3 &vec) const;
			Vector3 operator / (const Vector3 &vec) const;

			Vector3	normalize() const;

			float dot(const Vector3 &vec) const;

			Vector3	cross(const Vector3 &vec) const;
		};

	}
}

std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Vector3 &pos);

#endif