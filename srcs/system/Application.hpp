/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:48:23 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 17:48:27 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_APPLICATION_HPP
# define LCPPGL_APPLICATION_HPP

# include "lcppgl.hpp"
# include "Singleton.hpp"
# include <vector>

// TODO : The application should be able to handle multiple windows
// TODO : The application should be able to handle multiple contexts
// TODO : The renderer should be a class.

namespace lcppgl
{
	// This class is a singleton used to create a window and manage it.
	// The application is created by the first call to the get_instance() method.
	// The application is automatically destroyed. (The method quit() is deprecated)
	class Application : public lcppgl::Singleton
	{
		private:
			SDL_Window		*_window;
			SDL_Renderer	*_renderer;
			
			// Tell if the application is running
			bool			_is_running;
			unsigned int	_fps_limit;
			// Functor to call in the event_manager
			std::vector<void (*)(SDL_Event)>	_event_functors;
			// void			(*_event_functor)(SDL_Event);

			// Functor to call in the render_manager
			std::vector<void (*)(void)>	_render_functors;
			// void			(*_render_functor)();
			
			Application(void);
			
			void	event_manager(void);
			void	render_manager(void);

		public:
			~Application(void);
			
			static Application &	instance(void);

			int		width(void) const;
			int		height(void) const;

			bool	is_fullscreen(void) const;
			bool	is_resizable(void) const;
			bool	is_borderless(void) const;

			void	set_window_title(const std::string & title);
			void	set_window_size(const int width, const int height);
			void	set_window_fullscreen(const bool fullscreen);
			void	set_window_resizable(const bool resizable);
			void	set_window_borderless(const bool borderless);
			void	set_render_draw_color(const SDL_Color & color);
			void	set_render_draw_color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
			// If the fps is set to 0 the fps are not limited.
			void	set_fps_limit(const unsigned int fps);

			void	clear_window(void);
			void	present_window(void);

			void	put_outlined_rect(const SDL_Rect & rect);
			void	put_filled_rect(const SDL_Rect & rect);

			void	run(void);
			void	stop(void);

			__attribute__ ((deprecated)) void	quit(void);

			// Return the index of the function in the functor.
			int		add_event_functor(void (*functor)(SDL_Event));
			void	remove_event_functor(int index);
			// Return the index of the function in the functor.
			int		add_render_functor(void (*functor)(void));
			void	remove_render_functor(int index);
	};
}

#endif