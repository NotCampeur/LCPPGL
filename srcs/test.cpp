/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/10 14:02:52 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

void exit_input(lcppgl::Context &context)
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
				{
					context.remove_render_functor(0);
					lcppgl::Application::instance().stop();
				}
				else if (event.key.keysym.sym == SDLK_F11)
				{
					context.set_fullscreen(!context.is_fullscreen());
					if (context.is_fullscreen())
						context.set_size(1920, 1080);
					else
						context.set_size(800, 600);
				}
				break;
			default:
				break;
		}
	}
}

// Put two overlapping rectangles on the screen to test color blending.
void overlapping_rectangles(lcppgl::Context &context)
{
	lcppgl::Printer render(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 25);
	lcppgl::tools::Color red;
	lcppgl::tools::Color green;

	red = lcppgl::tools::Color(255, 0, 0, 120);
	green = lcppgl::tools::Color(0, 255, 0, 255);
	render.clear();
	SDL_SetRenderDrawBlendMode(context.renderer(), SDL_BLENDMODE_ADD);

	render.put_filled_rect(lcppgl::tools::Rectangle(400, 0, 400, 400),
						   red);
	render.put_filled_rect(lcppgl::tools::Rectangle(400, 200, 400, 400),
						   green);

	render.put_filled_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
						   red + green);

	render.put_outlined_rect(lcppgl::tools::Rectangle(0, 200, 400, 200),
							 lcppgl::tools::Color(255, 255, 255, 255));
	render.put_outlined_rect(lcppgl::tools::Rectangle(400, 200, 400, 200),
							 lcppgl::tools::Color(255, 255, 255, 255));

	writer.put_text("Actual", lcppgl::tools::Rectangle(150, 300, 100, 25),
					lcppgl::tools::Color(0, 0, 0, 255));
	writer.put_text("Expected", lcppgl::tools::Rectangle(550, 300, 100, 25),
					lcppgl::tools::Color(0, 0, 0, 255));
	render.present();
}

#include <sstream> // Needed since you can't use to_string() in C++98.
// Put random text on the screen at rendom position to test text rendering.
// Put text on the screen in the three different ways.
void text_rendering(lcppgl::Context &context)
{
	lcppgl::Printer render(context);
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 80);
	context.set_fps_limit(2);

	render.clear();
	writer.put_text("Hello World!", lcppgl::tools::Rectangle(20, 50, 480, 80),
					lcppgl::tools::Color(255, 255, 255, 255));
	writer.put_text_and_bg("Hello World!", lcppgl::tools::Rectangle(20, 150, 480, 80),
						   lcppgl::tools::Color(255, 255, 255, 255), lcppgl::tools::Color(100, 100, 100, 255));
	writer.put_pretty_text("Hello World!", lcppgl::tools::Rectangle(20, 250, 480, 80),
						   lcppgl::tools::Color(255, 255, 255, 255));

	std::ostringstream nb;

	nb << rand() % 100;
	writer.put_text(nb.str(), lcppgl::tools::Rectangle(rand() % (context.width() - 40), rand() % (context.height() - 80) + 40, 40, 40),
					lcppgl::tools::Color(rand() % 255, rand() % 255, rand() % 255, 255));
	render.present();
}

void great_rendering(lcppgl::Context &context)
{
	try
	{
		lcppgl::tools::Texture texture(context, "./ressources/great.png");
		lcppgl::tools::Rectangle img_rect(0, 0, texture.width(), texture.height());
		lcppgl::tools::Rectangle screen_rect(context.width() / 3, context.height() / 3, context.width() / 3, context.height() / 3);
		
		lcppgl::Printer render(context);

		context.set_fps_limit(2);
		
		render.clear();
		texture.render(&img_rect, &screen_rect);
		render.present();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void grid_rendering(lcppgl::Context &context)
{
	try
	{
		lcppgl::Printer render(context);
		
		context.set_fps_limit(0);
		render.clear();
		

		for (int i(0); i < context.height() / (20 + 1); i++)
		{
			for (int j(0); j < context.width() / (20 + 1); j++)
			{
				if (rand() % 2 == 0)
					render.set_draw_color(lcppgl::tools::Color(0, 0, 0, 255));
				else
					render.set_draw_color(lcppgl::tools::Color(200, 200, 200, 255));
				render.put_filled_rect(lcppgl::tools::Rectangle(j * (20 + 1), i * (20 + 1), 20, 20));
			}
		}

		render.set_draw_color(lcppgl::tools::Color(0, 0, 0, 255));
		render.present();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	choose_the_test(lcppgl::Context &context)
{
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 100);
	lcppgl::Printer render(context);

	int size(5);
	std::string str[size] = {"1. overlapping rectangles",
							"2. text rendering",
							"3. image rendering",
							"4. grid rendering",
							"5. Exit the program"};
	render.clear();
	for (int i(0); i < size; ++i)
	{
		writer.put_pretty_text(str[i], lcppgl::tools::Rectangle(15,
			context.height() / size * i + 30, context.width() - 30, 80),
			lcppgl::tools::Color(255, 255, 255, 255));
	}
	render.present();

	SDL_Event event;
	for (bool choosen(false); choosen != true;)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				choosen = true;
				break;
			case SDL_KEYDOWN:
				choosen = true;
				if (event.key.keysym.sym == SDLK_ESCAPE ||
					event.key.keysym.sym == SDLK_KP_5 ||
					event.key.keysym.sym == SDLK_5)
					context.stop();
				else if (event.key.keysym.sym == SDLK_KP_1 || event.key.keysym.sym == SDLK_1)
						context.add_render_functor(overlapping_rectangles);
				else if (event.key.keysym.sym == SDLK_KP_2 || event.key.keysym.sym == SDLK_2)
					context.add_render_functor(text_rendering);
				else if (event.key.keysym.sym == SDLK_KP_3 || event.key.keysym.sym == SDLK_3)
					context.add_render_functor(great_rendering);
				else if (event.key.keysym.sym == SDLK_KP_4 || event.key.keysym.sym == SDLK_4)
					context.add_render_functor(grid_rendering);
				else
					choosen = false;
				break;
			default:
				break;
		}
	}
	render.clear();
}

int main(void)
{
	try
	{
		lcppgl::Context &main_context = lcppgl::Application::instance().create_context();

		main_context.add_event_functor(exit_input);
		while (main_context.is_running())
		{
			choose_the_test(main_context);
			lcppgl::Application::instance().run();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	return EXIT_SUCCESS;
}