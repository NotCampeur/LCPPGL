/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2021/11/25 19:46:03 by ldutriez         ###   ########.fr       */
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
	lcppgl::tools::Rectangle rect_one(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	lcppgl::tools::Rectangle rect_two(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	
	rect_one.move(rand() % (context.width() - rect_one.width()), rand() % (context.height() - rect_one.height()));
	rect_two.move(rand() % (context.width() - rect_two.width()), rand() % (context.height() - rect_two.height()));
	render.clear();
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_one);
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_two);
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