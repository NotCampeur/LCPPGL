/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:45 by ldutriez          #+#    #+#             */
/*   Updated: 2022/11/03 15:10:20 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <algorithm>
#include "Vector3.hpp"

namespace lcppgl
{
	namespace tools
	{
		float to_radian(int degree)
		{
			return (static_cast<float>(degree * (M_PI / 180)));
		}

		// Setting max at 0 turn the rasterization to voxelization.
		float clamp(float val, float min = 0.0f, float max = 1.0f)
		{
			return std::max(min, std::min(val, max));
		}

		float interpolate(float min, float max, float gradient)
		{
			return (min + (max - min) * clamp(gradient));
		}
		
		// Compute the cosine of the angle between the light vector and the normal
		// Returns a value between 0 and 1
		float computeNDotL(const Vector3 & vertex, const Vector3 & normal,
							const Vector3 & lightPosition)
		{
			Vector3 lightDirection = lightPosition - vertex;
			
			normal.normalize();
			lightDirection.normalize();
			
			return std::max(0.0f, normal.dot(lightDirection));
		}
	}
}