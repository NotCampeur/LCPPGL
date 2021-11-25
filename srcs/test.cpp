/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 17:13:06 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

void	exit_input(lcppgl::Context & context)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					context.stop();
				else if (event.key.keysym.sym == SDLK_F11)
					context.set_fullscreen(!context.is_fullscreen());
				break;
			default:
				break;
		}
	}
}

// Put a rectangle on the screen with random position and color.
void	random_rectangle(lcppgl::Context & context)
{
	lcppgl::Render render(context);

	render.clear();
	SDL_Rect rect;
	rect.w = rand() % 100 + 50;
	rect.h = rand() % 100 + 50;
	rect.x = rand() % (context.width() - rect.w);
	rect.y = rand() % (context.height() - rect.h);
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect);
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	rect.w = rand() % 100 + 50;
	rect.h = rand() % 100 + 50;
	rect.x = rand() % (context.width() - rect.w);
	rect.y = rand() % (context.height() - rect.h);
	render.put_filled_rect(rect);
	render.set_draw_color(0, 0, 0, 255);
	render.present();
}

int	main(void)
{
	try
	{
		lcppgl::Context & main_context = lcppgl::Application::instance().create_context();
		main_context.set_fps_limit(5);
		main_context.add_event_functor(exit_input);
		main_context.add_render_functor(random_rectangle);

		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}