/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcppgl_tools.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:20:57 by ldutriez          #+#    #+#             */
/*   Updated: 2023/02/13 20:19:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_TOOLS_HPP
# define LCPPGL_TOOLS_HPP

// Render tools
# include "Rectangle.hpp"
# include "Color.hpp"
# include "Texture.hpp"

// Math tools

namespace lcppgl
{
	namespace tools
	{
		/**
		 * @brief Take an angle in degree and return an angle in radian
		 */
		float to_radian(int degree);

		/**
		 * @brief Contain a value in a range.
		 * 
		 * @param val The value you want to contain.
		 * @param min The minimal wanted value, default 0.
		 * @param max The maximal wanted value, default 1.
		 * @return Either min, max or the value.
		 */
		float clamp(float val, float min = 0.0f, float max = 1.0f);

		/**
		 * @brief Compute a value between min and max according the gradient.
		 * 
		 * @param min The starting value of the range.
		 * @param max The end value of the range.
		 * @param gradient The percent toward the end value.
		 * @return A float containing the interpolation.
		 */
		float interpolate(float min, float max, float gradient);
	}
}

# include "Vector3.hpp"
# include "Matrix4x4.hpp"
# include "Face.hpp"
# include "Mesh.hpp"

#endif