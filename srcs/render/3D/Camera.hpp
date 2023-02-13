/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:05:27 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/27 15:38:55 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_CAMERA_HPP
# define LCPPGL_CAMERA_HPP

# include "Vector3.hpp"

namespace lcppgl
{
	struct Camera
	{
		tools::Vector3	pos;
		tools::Vector3	target;

		Camera(const tools::Vector3 & position = tools::Vector3(),
				const tools::Vector3 & direction = tools::Vector3());
		Camera(const Camera & to_copy);
		Camera & operator = (const Camera & to_assign);
		~Camera();
	};
}

#endif