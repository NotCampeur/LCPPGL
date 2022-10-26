/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZPrinter.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:41:59 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/25 16:00:19 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZPrinter.hpp"


lcppgl::ZPrinter::ZPrinter(lcppgl::Context & context)
: _current_context(context)
, _z_buffer(new float[_current_context.width() * _current_context.height()])
{
	float	max(std::numeric_limits<float>::max());
	int		buff_size(_current_context.width() * _current_context.height());
	
	for (int i(0); i < buff_size; ++i)
		_z_buffer[i] = max;
}

lcppgl::ZPrinter::~ZPrinter()
{
	delete []_z_buffer;
}

void
lcppgl::ZPrinter::set_current_context(lcppgl::Context & context)
{
	_current_context = context;
}

void
lcppgl::ZPrinter::set_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), color.r, color.g, color.b, color.a);
}

void
lcppgl::ZPrinter::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), r, g, b, a);
}

void
lcppgl::ZPrinter::put_outlined_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::ZPrinter::put_outlined_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_filled_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::ZPrinter::put_filled_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_line(const lcppgl::tools::Rectangle & points)
{
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
}

void
lcppgl::ZPrinter::put_line(const lcppgl::tools::Rectangle & points, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int width(_current_context.width());
	int height(_current_context.height());
	
	if (x1 < 0 || x2 < 0 || x3 < 0
		|| x1 >= width || x2 >= width || x3 >= width
		|| y1 < 0 || y2 < 0 || y3 < 0
		|| y1 >= height || y2 >= height || y3 >= height)
		return ;

	SDL_RenderDrawLine(_current_context.renderer(), x1, y1, x2, y2);
	SDL_RenderDrawLine(_current_context.renderer(), x2, y2, x3, y3);
	SDL_RenderDrawLine(_current_context.renderer(), x3, y3, x1, y1);
}

void
lcppgl::ZPrinter::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
				const tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);

	put_triangle(x1, y1, x2, y2, x3, y3);

	set_draw_color(r, g, b, a);
}

void
lcppgl::ZPrinter::put_pixel(int x, int y, float z, const tools::Color & color)
{
	Uint8 r, g, b, a;

	int width(_current_context.width());
	int height(_current_context.height());
	
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	int buffer_pos(y * width + x);
	if (z <= _z_buffer[buffer_pos])
	{
		_z_buffer[buffer_pos] = z;
		SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
		set_draw_color(color);
		SDL_RenderDrawPoint(_current_context.renderer(), x, y);
		set_draw_color(r, g, b, a);
	}
}

void
lcppgl::ZPrinter::clear(void)
{
	SDL_RenderClear(_current_context.renderer());
}

void
lcppgl::ZPrinter::present(void)
{
	SDL_RenderPresent(_current_context.renderer());
}