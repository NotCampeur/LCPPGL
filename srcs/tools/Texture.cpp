/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:13:39 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/20 14:33:21 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"

lcppgl::tools::Texture::Texture(Context &context, SDL_Surface *surface, bool free_surface)
	: _context(context), _texture(NULL)
{
	if (surface == NULL)
		throw std::runtime_error("Can not create texture from NULL surface");
	_texture = SDL_CreateTextureFromSurface(_context.renderer(), surface);
	if (_texture == NULL)
		throw std::runtime_error(std::string("Can not create texture from surface: ") + SDL_GetError());
	_width = surface->w;
	_height = surface->h;
	if (free_surface == true)
		SDL_FreeSurface(surface);
}

lcppgl::tools::Texture::Texture(Context &context, const std::string &path)
	: _context(context)
{
	SDL_Surface *img;

	img = IMG_Load(path.c_str());
	if (img == NULL)
		throw std::invalid_argument(IMG_GetError());
	_width = img->w;
	_height = img->h;
	_texture = SDL_CreateTextureFromSurface(lcppgl::Application::instance().context().renderer(), img);
	if (_texture == NULL)
		throw std::invalid_argument(SDL_GetError());
	SDL_FreeSurface(img);
}

lcppgl::tools::Texture::~Texture(void)
{
	if (_texture)
		SDL_DestroyTexture(_texture);
}

void lcppgl::tools::Texture::render(const Rectangle *src, const Rectangle *dst)
{
	if (SDL_RenderCopy(_context.renderer(), _texture, (const SDL_Rect *)src, (const SDL_Rect *)dst) == -1)
		throw std::runtime_error(std::string("SDL_RenderCopy: ") + SDL_GetError());
}

int lcppgl::tools::Texture::width(void) const
{
	return _width;
}

int lcppgl::tools::Texture::height(void) const
{
	return _height;
}