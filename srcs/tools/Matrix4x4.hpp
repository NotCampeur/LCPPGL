/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix4x4.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:33:00 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/27 15:36:26 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_MATRIX_4X4_HPP
# define LCPPGL_MATRIX_4X4_HPP

# include <iostream>
# include <cmath>
# include "Vector3.hpp"

namespace lcppgl
{
	namespace tools
	{
		/**
		 * @brief A 4 by 4 matrix.
		 */
		struct Matrix4x4
		{
			float	matrix[4][4];

			Matrix4x4();

			Matrix4x4(const Matrix4x4 &to_copy);

			Matrix4x4 &operator = (const Matrix4x4 & to_assign);

			~Matrix4x4();

			Matrix4x4	x_rotation(const float ax) const;

			Matrix4x4	y_rotation(const float ay) const;

			Matrix4x4	z_rotation(const float az) const;

			void	set_to_rotate(const float x, const float y, const float z);

			void	set_to_translate(const float dx, const float dy, const float dz);

			void	set_to_scale(const float dx, const float dy, const float dz);

			/**
			* @brief Set the matrix to perform view transformation (right handed)
			* 
			* @param cam_pos The Camera.pos vector3 telling where the camera is.
			* 					Used for translation.
			* @param cam_target The Camera.target vector3 telling where the camera look at.
			* @param up_point Usually [0, 1, 0], tells where is the up of the world.
			*/
			static Matrix4x4	look_at(const Vector3 &cam_pos, const Vector3 &cam_target,
								const Vector3 &up_point);

			static Matrix4x4 perspective(float fov, float ratio, float z_far, float z_near);

			Matrix4x4	operator * (const Matrix4x4 &m) const;

			Vector3 operator * (const Vector3 & v) const;
		};
	}
}

std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Matrix4x4 &matrix);

#endif