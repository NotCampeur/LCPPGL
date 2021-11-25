/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:05:44 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 20:33:27 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_RENDER_HPP
# define LCPPGL_RENDER_HPP

# include "lcppgl.hpp"

namespace lcppgl {namespace tools {class Rectangle;}}

namespace lcppgl
{
	class Render
	{
		private:
			Context	& _current_context;
			
		public:
			Render(Context & context);
			~Render();

			void	set_current_context(Context & context);

			void	set_draw_color(const SDL_Color & color);
			void	set_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

			void	put_outlined_rect(const lcppgl::tools::Rectangle & rect);
			void	put_filled_rect(const lcppgl::tools::Rectangle & rect);

			void	clear(void);
			void	present(void);
	};
}

#endif