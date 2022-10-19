/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:53:01 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/11 08:57:00 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Printer.hpp"


lcppgl::Printer::Printer(lcppgl::Context & context)
: _current_context(context)
{}

lcppgl::Printer::~Printer()
{}

void
lcppgl::Printer::set_current_context(lcppgl::Context & context)
{
	_current_context = context;
}

void
lcppgl::Printer::set_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), color.r, color.g, color.b, color.a);
}

void
lcppgl::Printer::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), r, g, b, a);
}

void
lcppgl::Printer::put_outlined_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::Printer::put_outlined_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::Printer::put_filled_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::Printer::put_filled_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
	set_draw_color(r, g, b, a);
}

void
lcppgl::Printer::put_line(const lcppgl::tools::Rectangle & points)
{
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
}

void
lcppgl::Printer::put_line(const lcppgl::tools::Rectangle & points, const lcppgl::tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);
	SDL_RenderDrawLine(_current_context.renderer(),
		points.x(), points.y(), points.width(), points.height());
	set_draw_color(r, g, b, a);
}

void
lcppgl::Printer::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	SDL_RenderDrawLine(_current_context.renderer(), x1, y1, x2, y2);
	SDL_RenderDrawLine(_current_context.renderer(), x2, y2, x3, y3);
	SDL_RenderDrawLine(_current_context.renderer(), x3, y3, x1, y1);
}

void
lcppgl::Printer::put_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
				const tools::Color & color)
{
	Uint8 r, g, b, a;

	SDL_GetRenderDrawColor(_current_context.renderer(), &r, &g, &b, &a);
	set_draw_color(color);

	put_triangle(x1, y1, x2, y2, x3, y3);

	set_draw_color(r, g, b, a);
}
void
lcppgl::Printer::clear(void)
{
	SDL_RenderClear(_current_context.renderer());
}

void
lcppgl::Printer::present(void)
{
	SDL_RenderPresent(_current_context.renderer());
}