/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2021/12/02 07:52:05 by ldutriez         ###   ########.fr       */
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
	lcppgl::Printer render(context);
	lcppgl::tools::Rectangle rect_one(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	lcppgl::tools::Rectangle rect_two(0, 0, rand() % 100 + 50, rand() % 100 + 50);
	
	rect_one.move(rand() % (context.width() - rect_one.width()), rand() % (context.height() - rect_one.height()));
	rect_two.move(rand() % (context.width() - rect_two.width()), rand() % (context.height() - rect_two.height()));
	// render.clear();
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_one);
	render.set_draw_color(rand() % 255, rand() % 255, rand() % 255, 255);
	render.put_filled_rect(rect_two);
	render.set_draw_color(0, 0, 0, 255);
	render.present();
}

// Put two overlapping rectangles on the screen to test color blending.
void	overlapping_rectangles(lcppgl::Context & context)
{
	lcppgl::Printer render(context);
	lcppgl::tools::Color add_of_red_and_blue;
	lcppgl::tools::Color sub_of_red_and_fifty;
	
	add_of_red_and_blue = lcppgl::tools::Color(255, 0, 0, 120) + lcppgl::tools::Color(0, 255, 0, 255);
	sub_of_red_and_fifty = lcppgl::tools::Color(255, 255, 255, 255) - lcppgl::tools::Color(0, 255, 0, 255);
	render.clear();
	SDL_SetRenderDrawBlendMode(context.renderer(), SDL_BLENDMODE_ADD);
	render.put_filled_rect(lcppgl::tools::Rectangle(0, 222, 800, 6),
		lcppgl::tools::Color(255, 255, 255, 54));

	render.put_filled_rect(lcppgl::tools::Rectangle(0, 200, 250, 50),
		add_of_red_and_blue);
		
	render.put_filled_rect(lcppgl::tools::Rectangle(250, 150, 500, 100),
		lcppgl::tools::Color(255, 0, 0, 120));
	render.put_filled_rect(lcppgl::tools::Rectangle(250, 200, 500, 100),
		lcppgl::tools::Color(0, 255, 0, 255));
	
	render.put_filled_rect(lcppgl::tools::Rectangle(0, 0, 800, 50),
		sub_of_red_and_fifty);
	render.put_filled_rect(lcppgl::tools::Rectangle(0, 50, 800, 50),
		lcppgl::tools::Color(255, 0, 255, 255));
	render.present();
}

int	main(void)
{
	try
	{
		lcppgl::Context & main_context = lcppgl::Application::instance().create_context();
		// main_context.set_fps_limit(5);
		main_context.add_event_functor(exit_input);
		main_context.add_render_functor(overlapping_rectangles);

		lcppgl::Application::instance().run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}