/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:58:02 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/02 05:26:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Color.hpp"

lcppgl::tools::Color::Color(void)
{
	_r = 0;
	_g = 0;
	_b = 0;
	_a = 0;
}

lcppgl::tools::Color::Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
: _r(r), _g(g), _b(b), _a(a)
{}

lcppgl::tools::Color::Color(const Color & color)
{
	*this = color;
}

lcppgl::tools::Color::~Color(void)
{}

lcppgl::tools::Color	&
lcppgl::tools::Color::operator=(const Color & color)
{
	if (this != &color)
	{
		_r = color._r;
		_g = color._g;
		_b = color._b;
		_a = color._a;
	}
	return (*this);
}

// Do an additive blending of the two colors
lcppgl::tools::Color	&
lcppgl::tools::Color::operator+(const Color & color)
{
	float	base_alpha = color._a / 255.0f;
	float	inv_alpha = _a / 255.0f;
	
	_r = static_cast<Uint8>((color._r * base_alpha) + (_r * inv_alpha));
	_g = static_cast<Uint8>((color._g * base_alpha) + (_g * inv_alpha));
	_b = static_cast<Uint8>((color._b * base_alpha) + (_b * inv_alpha));
	_a = color._a;
	return (*this);
}

// Do a sort of substractive blending of the two colors
lcppgl::tools::Color	&
lcppgl::tools::Color::operator-(const Color & color)
{
	float	base_alpha = color._a / 255.0f;
	
	_r = ((color._r * base_alpha) >= _r) ? 0 : _r - (color._r * base_alpha);
	_g = ((color._g * base_alpha) >= _g) ? 0 : _g - (color._g * base_alpha);
	_b = ((color._b * base_alpha) >= _b) ? 0 : _b - (color._b * base_alpha);
	return (*this);
}

bool
lcppgl::tools::Color::operator==(const Color & color)
{
	return (_r == color._r && _g == color._g && _b == color._b && _a == color._a);
}

bool
lcppgl::tools::Color::operator!=(const Color & color)
{
	return !(*this == color);
}

Uint8
lcppgl::tools::Color::r(void) const
{
	return (_r);
}

Uint8
lcppgl::tools::Color::g(void) const
{
	return (_g);
}

Uint8
lcppgl::tools::Color::b(void) const
{
	return (_b);
}

Uint8
lcppgl::tools::Color::a(void) const
{
	return (_a);
}

void
lcppgl::tools::Color::set_r(const Uint8 r)
{
	_r = r;
}

void
lcppgl::tools::Color::set_g(const Uint8 g)
{
	_g = g;
}

void
lcppgl::tools::Color::set_b(const Uint8 b)
{
	_b = b;
}

void
lcppgl::tools::Color::set_a(const Uint8 a)
{
	_a = a;
}