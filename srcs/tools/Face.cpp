/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Face.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:15:12 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/26 16:20:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Face.hpp"

using namespace lcppgl::tools;

Face::Face(int _a, int _b, int _c)
: a(_a), b(_b), c(_c)
{}

Face::Face(const Face & to_copy)
: a(to_copy.a), b(to_copy.b), c(to_copy.c)
{}

Face &
Face::operator = (const Face & to_assign)
{
	if (this != &to_assign)
	{
		a = to_assign.a;
		b = to_assign.b;
		c = to_assign.c;
	}
	return *this;
}

Face::~Face()
{}

std::ostream &operator<<(std::ostream & os, const lcppgl::tools::Face &face)
{
	os << "[" << face.a << '-' << face.b << '-' << face.c << ']';
	return os;
}