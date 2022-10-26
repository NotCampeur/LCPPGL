/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:05:27 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:07:14 by ldutriez         ###   ########.fr       */
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
	};
}

#endif