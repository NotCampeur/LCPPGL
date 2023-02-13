/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:28:45 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:00:37 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <algorithm>

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
	}
}