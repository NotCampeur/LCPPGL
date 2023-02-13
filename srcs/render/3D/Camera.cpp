/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:35:29 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/27 15:20:41 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

using namespace lcppgl;

Camera::Camera(const tools::Vector3 & position, const tools::Vector3 & direction)
: pos(position), target(direction)
{}

Camera::Camera(const Camera & to_copy)
: pos(to_copy.pos), target(to_copy.target)
{}

Camera &
Camera::operator = (const Camera & to_assign)
{
	if (this != &to_assign)
	{
		pos = to_assign.pos;
		target = to_assign.target;
	}
	return *this;
}

Camera::~Camera()
{}