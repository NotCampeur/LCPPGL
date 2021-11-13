/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/13 18:12:47 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

void	exit_input(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			lcppgl::Application::instance().stop();
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				lcppgl::Application::instance().stop();
			else if (event.key.keysym.sym == SDLK_F11)
				lcppgl::Application::instance().set_window_fullscreen(!lcppgl::Application::instance().is_fullscreen());
			break;
		default:
			break;
	}
}

// Put a rectangle on the screen with random position and color.
void	random_rectangle(void)
{
	lcppgl::Application::instance().clear_window();
	SDL_Rect rect;
	rect.w = rand() % 100 + 50;
	rect.h = rand() % 100 + 50;
	rect.x = rand() % (lcppgl::Application::instance().width() - rect.w);
	rect.y = rand() % (lcppgl::Application::instance().height() - rect.h);
	lcppgl::Application::instance().set_render_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	lcppgl::Application::instance().put_filled_rect(rect);
	lcppgl::Application::instance().set_render_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	rect.w = rand() % 100 + 50;
	rect.h = rand() % 100 + 50;
	rect.x = rand() % (lcppgl::Application::instance().width() - rect.w);
	rect.y = rand() % (lcppgl::Application::instance().height() - rect.h);
	lcppgl::Application::instance().put_filled_rect(rect);
	lcppgl::Application::instance().set_render_draw_color(0, 0, 0, 255);
	lcppgl::Application::instance().present_window();
}

int	main(void)
{
	try
	{
		lcppgl::Application::instance().set_window_title("Testing of LCPPGL");
		lcppgl::Application::instance().set_fps_limit(5);
		lcppgl::Application::instance().add_event_functor(exit_input);
		lcppgl::Application::instance().add_render_functor(random_rectangle);
		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return EXIT_SUCCESS;
}