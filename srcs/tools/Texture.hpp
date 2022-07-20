/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:03:08 by ldutriez          #+#    #+#             */
/*   Updated: 2022/07/20 14:19:49 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_TEXTURE_HPP
#define LCPPGL_TEXTURE_HPP

#include "lcppgl.hpp"

/**
 * @brief Texture class
 * @file Texture.hpp
 * @author @NotCampeur
 * @version 0.1
 * @date 2020-12-07
 */

namespace lcppgl
{
	namespace tools
	{
		class Rectangle;

		class Texture
		{
		private:
			Context &_context;
			SDL_Texture *_texture;
			int _width;
			int _height;

		public:
			/**
			 * @brief Construct a new Texture object for the given context via the given surface.
			 *
			 * @param context The context to use.
			 * @param surface The surface to transform into a texture.
			 * @param free_surface If true, the surface will be freed after the texture creation with SDL_FreeSurface.
			 *
			 * @throw std::runtime_error If the texture creation failed.,
			 * @throw std::runtime_error If the surface is null.
			 */
			Texture(Context &context, SDL_Surface *surface, bool free_surface = true);

			/**
			 * @brief Construct a new Texture object from an image file.
			 * 
			 * @param context The context link to the texture that will be use to render.
			 * @param path Path to the image file.
			 * 
			 * @throw std::runtime_error If the texture creation failed.
			 * @throw std::runtime_error If the surface creation fail.
			 */
			Texture(Context &context, const std::string &path);
			~Texture();

			/**
			 * @brief Print the texture to the context's renderer.
			 *
			 * @param src The dimensions of the texture to print. NULL to use the entire texture.
			 * @param dst The dimensions of the destination to print the texture. NULL to use the entire context's renderer.
			 *
			 * @details The texture will be stretched to fill the dst rectangle.
			 *
			 * @throw std::runtime_error If SDL_RenderCopy failed.
			 */
			void render(const Rectangle *src, const Rectangle *dst);

			int width(void) const;
			int height(void) const;
		};
	}
}

#endif