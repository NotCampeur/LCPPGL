/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:53:01 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 20:36:11 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Render.hpp"


lcppgl::Render::Render(lcppgl::Context & context)
: _current_context(context)
{}

lcppgl::Render::~Render()
{}

void
lcppgl::Render::set_current_context(lcppgl::Context & context)
{
	_current_context = context;
}

void
lcppgl::Render::set_draw_color(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), color.r, color.g, color.b, color.a);
}

void
lcppgl::Render::set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a)
{
	SDL_SetRenderDrawColor(_current_context.renderer(), r, g, b, a);
}

void
lcppgl::Render::put_outlined_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderDrawRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::Render::put_filled_rect(const lcppgl::tools::Rectangle & rect)
{
	SDL_RenderFillRect(_current_context.renderer(), (SDL_Rect *)&rect);
}

void
lcppgl::Render::clear(void)
{
	SDL_RenderClear(_current_context.renderer());
}

void
lcppgl::Render::present(void)
{
	SDL_RenderPresent(_current_context.renderer());
}