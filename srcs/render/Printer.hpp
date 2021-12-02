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

			void	put_outlined_rect(const lcppgl::tools::Rectangle & rect);
			void	put_outlined_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color);
			void	put_filled_rect(const lcppgl::tools::Rectangle & rect);
			void	put_filled_rect(const lcppgl::tools::Rectangle & rect, const lcppgl::tools::Color & color);

			void	clear(void);
			void	present(void);
	};
}

#endif