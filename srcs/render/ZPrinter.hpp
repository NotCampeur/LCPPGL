/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZPrinter.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:38:32 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/24 12:09:35 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_ZPrinter_HPP
# define LCPPGL_ZPrinter_HPP

# include "lcppgl.hpp"
# include <limits> //Used by numeric_limits<T>
# include <cstring> //Used by memset

namespace lcppgl {namespace tools {class Rectangle;class Color;}}

namespace lcppgl
{
	class ZPrinter
	{
		private:
			Context	&	_current_context;
			float *		_z_buffer;

			ZPrinter &	operator = (const ZPrinter & to_copy);
		public:
			ZPrinter(Context & context);
			~ZPrinter();

			__attribute__ ((deprecated)) void	set_current_context(Context & context);

			void	set_draw_color(const SDL_Color & color);
			void	set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

			void	put_outlined_rect(const tools::Rectangle & rect);
			void	put_outlined_rect(const tools::Rectangle & rect, const tools::Color & color);
			void	put_filled_rect(const tools::Rectangle & rect);
			void	put_filled_rect(const tools::Rectangle & rect, const tools::Color & color);

			/**
			 * @brief Put a line in the linked context.
			 * 
			 * @param points A tools::Rectangle storing x1,y1 and x2,y2.
			 */
			void	put_line(const tools::Rectangle & points);

			/**
			 * @brief Put a line in the linked context.
			 * 
			 * @param points A tools::Rectangle storing x1,y1 and x2,y2.
			 * @param color The color to draw the line with.
			 */
			void	put_line(const tools::Rectangle & points,
								const tools::Color & color);

			//TODO : Do a Triangle class.
			void	put_triangle(int x1, int y1, int x2, int y2, int x3, int y3);
			void	put_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
									const tools::Color & color);

			void	put_pixel(int x, int y, float z, const tools::Color & color);
			
			void	clear(void);
			void	present(void);
	};
}

#endif