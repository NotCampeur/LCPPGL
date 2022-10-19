/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:59:07 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/19 13:42:51 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lcppgl.hpp"
#include <cmath>

int id;

#include <math.h>
#define PI2 6.28318530718

float timing = 0;
float freq = 440;

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
						context.set_size(1920, 1080);
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

void inner_triangle(lcppgl::Printer & printer,
				int i, int a_x, int a_y, int b_x, int b_y, int c_x, int c_y)
{
	lcppgl::tools::Color color(rand() % 255, rand() % 255, rand() % 255, 255);
	
	if (i == 0)
		return;
	
	int ab_center_x((a_x + b_x) / 2);
	int ab_center_y((a_y + b_y) / 2);
	int bc_center_x((b_x + c_x) / 2);
	int bc_center_y((b_y + c_y) / 2);
	int ca_center_x((c_x + a_x) / 2);
	int ca_center_y((c_y + a_y) / 2);

	printer.put_triangle(ab_center_x, ab_center_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y, color);

	inner_triangle(printer, i - 1,
	ab_center_x, ab_center_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y);

	inner_triangle(printer, i - 1,
	ab_center_x, ab_center_y, bc_center_x, bc_center_y, b_x, b_y);
	inner_triangle(printer, i - 1,
	a_x, a_y, ca_center_x, ca_center_y, ab_center_x, ab_center_y);
	inner_triangle(printer, i - 1,
	c_x, c_y, bc_center_x, bc_center_y, ca_center_x, ca_center_y);
}

// The Sierpinski Triangle
void	draw_triangle(lcppgl::Context &context)
{
	SDL_PauseAudioDevice(id, false);
	SDL_Delay(100);
	lcppgl::Printer printer(context);

	lcppgl::tools::Rectangle ab(context.width() / 2, 0, context.width() - 1, context.height() - 1);
	lcppgl::tools::Rectangle c(0, context.height() - 1);
	static lcppgl::tools::Color color(255, 255, 255, 255);
	static int i(0);
	static int y(1);

	printer.clear();
	context.set_fps_limit(y);

	printer.put_triangle(ab.x(), ab.y(), ab.width(), ab.height(), c.x(), c.y(), color);
	inner_triangle(printer, i, ab.x(), ab.y(), ab.width(), ab.height(), c.x(), c.y());

	printer.present();
	++i;
	if (i > 11)
		i = 0;
	freq = i * 400 + 400;
	++y;
	SDL_PauseAudioDevice(id, true);
}

void	draw_lines(lcppgl::Context &context)
{
	lcppgl::Printer printer(context);

	static lcppgl::tools::Rectangle line;
	static bool drawing(false);
	
	SDL_Event event;
	printer.clear();

	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				context.stop();
				return;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					context.remove_render_functor(0);
					lcppgl::Application::instance().stop();
					return;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					line.reset(event.motion.x, event.motion.y,
								event.motion.x, event.motion.y);
					drawing = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					drawing = false;
				break;
			case SDL_MOUSEMOTION:
				if (drawing)
					line.resize(event.motion.x, event.motion.y);
				break;
		}
		printer.put_line(line, lcppgl::tools::Color(0, 255, 0, 255));
		printer.present();
	}
}

void	draw_cube(lcppgl::Context &);

void	choose_the_test(lcppgl::Context &context)
{
	lcppgl::Writer writer(context, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 100);
	lcppgl::Printer render(context);

	int size(7);
	std::string str[size] = {"1. overlapping rectangles",
							"2. text rendering",
							"3. image rendering",
							"4. grid rendering",
							"5. Sierpinski Triangle",
							"6. Draw Lines(Deactivated for now)",
							"7. Cube"};
	render.clear();
	for (int i(0); i < size; ++i)
	{
		writer.put_pretty_text(str[i], lcppgl::tools::Rectangle(15,
			context.height() / size * i + 15, str[i].size() * 20, 80),
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
				if (event.key.keysym.sym == SDLK_ESCAPE)
					context.stop();
				else if (event.key.keysym.sym == SDLK_KP_1 || event.key.keysym.sym == SDLK_1)
						context.add_render_functor(overlapping_rectangles);
				else if (event.key.keysym.sym == SDLK_KP_2 || event.key.keysym.sym == SDLK_2)
					context.add_render_functor(text_rendering);
				else if (event.key.keysym.sym == SDLK_KP_3 || event.key.keysym.sym == SDLK_3)
					context.add_render_functor(great_rendering);
				else if (event.key.keysym.sym == SDLK_KP_4 || event.key.keysym.sym == SDLK_4)
					context.add_render_functor(grid_rendering);
				else if (event.key.keysym.sym == SDLK_KP_5 || event.key.keysym.sym == SDLK_5)
					context.add_render_functor(draw_triangle);
				else if (event.key.keysym.sym == SDLK_KP_6 || event.key.keysym.sym == SDLK_6)
				{
					choosen = false;
					break;
					context.add_render_functor(draw_lines);
				}
				else if (event.key.keysym.sym == SDLK_KP_7 || event.key.keysym.sym == SDLK_7)
					context.add_render_functor(draw_cube);
				else
					choosen = false;
				break;
			default:
				break;
		}
	}
	render.clear();
}

void callback(void* userdata, Uint8* stream, int len) {
	(void)userdata;
	short * snd = reinterpret_cast<short*>(stream);
	len /= sizeof(*snd);
	for(int i = 0; i < len; i++) //Fill array with frequencies, mathy-math stuff
	{
		snd[i] = 32000 * sin(timing);
		
		timing += freq * PI2 / 48000.0;
		if(timing >= PI2)
			timing -= PI2;
	}
}

void audio_test(void)
{
	SDL_AudioSpec spec, aspec; // the specs of our piece of "music"
	SDL_zero(spec);
	spec.freq = 48000; //declare specs
	spec.format = AUDIO_S16SYS;
	spec.channels = 1;
	spec.samples = 4096;
	spec.callback = callback;
	spec.userdata = NULL;

  //Open audio, if error, print
	if ((id = SDL_OpenAudioDevice(nullptr, 0, &spec, &aspec, SDL_AUDIO_ALLOW_ANY_CHANGE)) <= 0 )
	{
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}

	SDL_PauseAudioDevice(id, true);

}

int main(void)
{
	try
	{
		lcppgl::Context &main_context = lcppgl::Application::instance().create_context("lcppgl tests", 1920, 1080);

		main_context.add_event_functor(exit_input);
		audio_test();
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