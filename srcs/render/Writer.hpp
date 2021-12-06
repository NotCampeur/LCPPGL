/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Writer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:15:25 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/06 17:45:31 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_WRITER_HPP
# define LCPPGL_WRITER_HPP

# include "lcppgl.hpp"

namespace lcppgl {namespace tools {class Rectangle;class Color;}}

namespace lcppgl
{
	class Writer
	{
		private:
			lcppgl::Context &	_context;
			TTF_Font *			_font;
			std::string			_font_path;
			int					_font_size;

			SDL_Texture *	create_texture(SDL_Surface *surface); // Will be moved in a texture tool class.
			void			render_texture(SDL_Texture *tex, const SDL_Rect *src, const SDL_Rect *dst); // Will be moved in a texture tool class.
		public:
			Writer(lcppgl::Context & context, const std::string &path, int size);
			Writer(const Writer &src);
			~Writer(void);

			Writer &	operator=(const Writer &rhs);

			void		put_text(const std::string &text,
							const tools::Rectangle &rect,
							const tools::Color &color);
			void		put_text_and_bg(const std::string &text,
							const tools::Rectangle &rect,
							const tools::Color &color,
							const tools::Color &bg_color);
			void		put_pretty_text(const std::string &text,
							const tools::Rectangle &rect,
							const tools::Color &color);
			void		change_font(const std::string &path, int size);
	};
}

#endif