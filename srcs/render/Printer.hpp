/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:05:44 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 21:29:19 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_Printer_HPP
# define LCPPGL_Printer_HPP

# include "lcppgl.hpp"

namespace lcppgl {namespace tools {class Rectangle;class Color;}}

namespace lcppgl
{
	class Printer
	{
		private:
			Context	& _current_context;
			
		public:
			Printer(Context & context);
			~Printer();

			void	set_current_context(Context & context);

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

			void	clear(void);
			void	present(void);
	};
}

#endif